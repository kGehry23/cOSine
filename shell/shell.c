/********************************************************************************
 * @file    shell.c
 * 
 * @author  Kai Gehry
 * @date    2026-01-18
 *
 * @brief   cOSine shell
 * 
 ********************************************************************************
*/

/************************************
 * INCLUDES
 ************************************/
#include "../libc/stdio/stdio.h"
#include "../kernel/tty/terminal.h"
#include "../drivers/ps2/keyboard/keyboard_api.h"
#include "../drivers/disk/ata/ata.h"
#include "shell.h"
#include "../cpu/scheduling/scheduler.h"


/************************************
 * STATIC AND GLOBAL VARIABLES
 ************************************/

//Buffer for previously entered commands
static char* cmd_arr[128];
static const char *shell_prompt = "cOSh:$ ";

static task t1;
static task t2;
task shell;
extern task* current_task;

//Command list string
static const char* man_string = "\n\tSupported commands:\n\n"
                   "\tmultitask - Context switch example\n"
                   "\tls - list directory contents\n"
                   "\tcd - change current directory\n"
                   "\tmkdir - create new directory\n"
                   "\ttouch - create new file\n"
                   "\trm - delete file\n"
                   "\tcat - display contents of file\n"
                   "\tclear/cls - clear terminal contents\n"
                   "\n";


/************************************
 * FUNCTION DEFINITIONS
 ************************************/
                   
/*!
 * @brief Displays the command list
 * @return None
 */
static void display_command_list(void)
{
    printf("%s", man_string);
}

static void echo(void)
{
    int i = strlen("echo ");
    get_subset(i);
}

static void task_func(void)
{
    static int tsk_num = 1;
    printf("Task %d, TID: %d\n", tsk_num, current_task->tid);
    ++tsk_num;
    switch_state(&current_task->registers, &current_task->next_task->registers);
}

/*!
 * @brief Echos the input entered back to the user
 * @return None
 */

static void fcfs_example()
{
    task t1;
    task t2;
    task t3;
    task t4;

    create_new_task(&t1, task_func, get_eflags(), get_cr3());
    t1.next_task = &t2;
    create_new_task(&t2, task_func, get_eflags(), get_cr3());
    t2.next_task = &t3;
    create_new_task(&t3, task_func, get_eflags(), get_cr3());
    t3.next_task = &t4;
    create_new_task(&t4, task_func, get_eflags(), get_cr3());

    task task_queue[4] = {t1, t2, t3, t4};

    fcfs_sched(task_queue, 4);
}

static void task_test_2(void)
{
    printf("Test shell> ");

    while(1)
    {
        if(get_last_char() == '\n')
        {
            if(check_input("q"))
                break;

            printf("Test shell> ");
        }    
    }

    switch_state(&t2.registers,  &t1.registers);
}

static void task_test(void)
{
    printf("In test task...\n");

    switch_state(&t1.registers,  &t2.registers);

    printf("Got back into task 1\n");
    switch_state(&t1.registers,  &shell.registers);
}

static void task_example(void)
{
    printf("Test entered.\n");
    t1.registers.eip = (uint32_t)task_test;
    t2.registers.eip = (uint32_t)task_test_2;
    switch_state(&shell.registers, &t1.registers);  
}

/*!
 * @brief Executes an entered command
 * @return None
 */
static void exec_command(void)
{
    if(check_input("man") == true)
        display_command_list();

    else if (check_input("clear") == true || check_input("cls") == true)
        terminal_initialize();

    else if(check_input("echo") == true)
        echo();

    else if(check_input("multitask") == true)
    {
        task_example();
        printf("Back in shell\n");
    }

    else if(check_input("fcfs") == true)
        fcfs_example();

    else if(check_input("readsec") == true )
        read_sector(0);

    else if(check_input("writesec") == true )
        write_sector(0);

    else if (!check_input("\n"))
        printf("Command not found.\n");
}

/*!
 * @brief Initializes and starts cOSh
 * @return None
 */
void shell_init()
{
    create_new_task(&t1, task_test, get_eflags(), get_cr3());
    create_new_task(&t2, task_test_2, get_eflags(), get_cr3());

    //Clears the terminal 
    terminal_initialize();
    printf("cOSh:$ ");

    while(1)
    {
        if(get_last_char() == '\n')
        {
            exec_command();
            printf("%s", shell_prompt);
        } 
    }
}
