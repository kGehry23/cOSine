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
#include "shell.h"
#include "stdio.h"
#include "terminal.h"
#include "keyboard_api.h"
#include "ata.h"
#include "pit.h"
#include "scheduler.h"
#include "dispatcher.h"


/************************************
 * STATIC AND GLOBAL VARIABLES
 ************************************/

//Buffer for previously entered commands
static char* cmd_arr[128];

task shell;
extern task* current_task;

task t1;
task t2; 

static const char *shell_prompt = "cOSh:$ ";
//Command list
static const char* man_string = "\n\tSupported commands:\n\n"
                    "\thelp - list of supported commands\n"
                    "\tclear/cls - clear terminal contents\n"
                    "\techo - Print entered text to the terminal\n"
                    "\tsleep - Test timer interrupt. Sleep for 2 seconds.\n"
                    "\tfcfs - First come first served scheduling example\n"
                    "\tsjf - Shortest job first scheduling example\n"
                    "\trr - Round robin scheduling example\n"
                    "\treadsec - Read ATA disk sector.\n"
                    "\twritesec - Write to ATA disk sector.\n"
                    "\twipesec - Wipes the data written to an ATA disk sector.\n"
                    "\n";


/************************************
 * FUNCTION PROTOTYPES
 ************************************/
static void exec_command(void);
static void display_command_list(void);
static void echo(void);
static void fcfs_example(void);
static void sjf_example(void);
static void rr_example(void);
static void sched_func(void);
static void rr_sched_func(void);
static void print_shell_prompt(void);


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

//Initializes and starts the shell
void shell_init(void)
{
    //Clears the terminal 
    terminal_initialize();
    print_shell_prompt();
    enable_sleep_print();

    while(1)
    {
        if(get_last_char() == '\n')
        {
            exec_command();
            print_shell_prompt();
        } 
    }
}

 /*!
 * @brief Prints the shell prompt. Changes the color of the prompt.
 * @return None
 */
void print_shell_prompt(void)
{
    terminal_setcolour(SHELL_PROMPT_FG | SHELL_BG << 4);
    printf("%s", shell_prompt);
    terminal_setcolour(SHELL_FG | SHELL_BG << 4);
}
                   
/*!
 * @brief Displays the command list
 * @return None
 */
static void display_command_list(void)
{
    printf("%s", man_string);
}

/*!
 * @brief Echos the input entered back to the user
 * @return None
 */
static void echo(void)
{
    int i = strlen("echo ");
    get_subset(i);
}

/*!
 * @brief Function for fcfs and sjf tasks 
 * @return None
 */
static void sched_func(void)
{   
    printf("> ");

    printf("Task %d Started ", current_task->tid);
    sleep(current_task->execution_time);
    printf("Task %d Complete ", current_task->tid);
    printf("\n");

    dispatch(current_task, current_task->next_task);
}

/*!
 * @brief Function for round robin tasks
 * @return None
 */
static void rr_sched_func(void)
{   
    while(current_task->execution_time > 0)
    {
        printf("> ");
        printf("Task %d Started ", current_task->tid);

        //Execute for the time specified by the time quantum, and update the remaining execution time
        
        if((int32_t)current_task->execution_time - EXAMPLE_TIME_QUANTUM > 0)
        {
            current_task->execution_time -= EXAMPLE_TIME_QUANTUM;
            sleep(EXAMPLE_TIME_QUANTUM);
        }
        else
        {
            sleep(current_task->execution_time);
            current_task->execution_time = 0;
        }
        
        //If the task has completed, print a message
        if(current_task->execution_time == 0)
        {
            printf("Task %d Complete ", current_task->tid);
            current_task->state = TERMINATED;
        }

        printf("\n");
        dispatch(current_task, current_task->next_task);
    }
}

/*!
 * @brief First come first served scheduling example
 * @return None
 */
static void fcfs_example(void)
{
    task t1;
    task t2;
    task t3;
    task t4;

    create_new_task(&t1, sched_func, get_eflags(), get_cr3());
    t1.next_task = &t2;
    t1.execution_time = 2500;
    create_new_task(&t2, sched_func, get_eflags(), get_cr3());
    t2.next_task = &t3;
    t2.execution_time = 2000;
    create_new_task(&t3, sched_func, get_eflags(), get_cr3());
    t3.next_task = &t4;
    t3.execution_time = 4000;
    create_new_task(&t4, sched_func, get_eflags(), get_cr3());
    t4.execution_time = 500;

    printf("\nExecution times (milliseconds): \nTask %d: %d\n", t1.tid, t1.execution_time);
    printf("Task %d: %d\n", t2.tid, t2.execution_time);
    printf("Task %d: %d\n", t3.tid, t3.execution_time);
    printf("Task %d: %d\n\n", t4.tid, t4.execution_time);

    task task_queue[4] = {t1, t2, t3, t4};

    fcfs_sched(task_queue, 4);
}

/*!
 * @brief Shortest job first scheduling example
 * @return None
 */
static void sjf_example(void)
{
    task t1;
    task t2;
    task t3;
    task t4;

    create_new_task(&t1, sched_func, get_eflags(), get_cr3());
    t1.next_task = &t2;
    t1.execution_time = 2500;
    create_new_task(&t2, sched_func, get_eflags(), get_cr3());
    t2.next_task = &t3;
    t2.execution_time = 2000;
    create_new_task(&t3, sched_func, get_eflags(), get_cr3());
    t3.next_task = &t4;
    t3.execution_time = 4000;
    create_new_task(&t4, sched_func, get_eflags(), get_cr3());
    t4.execution_time = 500;

    printf("\nExecution times (milliseconds): \nTask %d: %d\n", t1.tid, t1.execution_time);
    printf("Task %d: %d\n", t2.tid, t2.execution_time);
    printf("Task %d: %d\n", t3.tid, t3.execution_time);
    printf("Task %d: %d\n\n", t4.tid, t4.execution_time);

    task task_queue[4] = {t1, t2, t3, t4};

    sjf_sched(task_queue, 4);
}

/*!
 * @brief Round robin scheduling example
 * @return None
 */
static void rr_example(void)
{
    task t1;
    task t2;
    task t3;
    task t4;

    create_new_task(&t1, rr_sched_func, get_eflags(), get_cr3());
    t1.next_task = &t2;
    t1.execution_time = 200;
    create_new_task(&t2, rr_sched_func, get_eflags(), get_cr3());
    t2.next_task = &t3;
    t2.execution_time = 400;
    create_new_task(&t3, rr_sched_func, get_eflags(), get_cr3());
    t3.next_task = &t4;
    t3.execution_time = 300;
    create_new_task(&t4, rr_sched_func, get_eflags(), get_cr3());
    t4.execution_time = 500;

    printf("Execution times (milliseconds) - Time Quantum = %d ms: \nTask %d: %d\n", EXAMPLE_TIME_QUANTUM, t1.tid, t1.execution_time);
    printf("Task %d: %d\n", t2.tid, t2.execution_time);
    printf("Task %d: %d\n", t3.tid, t3.execution_time);
    printf("Task %d: %d\n\n", t4.tid, t4.execution_time);

    task task_queue[4] = {t1, t2, t3, t4};

    rr_sched(task_queue, 4);
}

void test1(void)
{
    printf("Here\n");
    int i = 15;
    printf("value of i in t1: %d, at addr: %p\n", i, &i);

    switch_state(&t1.registers, &t2.registers);
    printf("value of i in t1: %d, at addr: %p\n", i, &i);
    switch_state(&t1.registers, &current_task->registers);
}

void test2(void)
{
    int j = 4;
    printf("value of j in t2: %d, at addr: %p\n", j, &j);

    switch_state(&t2.registers, &t1.registers);
}


static void virt_mem_example(void)
{
    task main;

    create_new_task(&t1, test1, get_eflags(), get_cr3());
    create_new_task(&t2, test2, get_eflags(), get_cr3());

    current_task = &main;

    printf("Got here\n");
    switch_state(&main.registers, &t1.registers);
    printf("Complete\n");
}

/*!
 * @brief Executes an entered command
 * @return None
 */
static void exec_command(void)
{
    if(check_input("help") == true)
        display_command_list();

    else if (check_input("clear") == true || check_input("cls") == true)
        terminal_initialize();

    else if(check_input("echo") == true)
        echo();

    else if(check_input("sleep") == true)
    {
        outb(PIC_MASTER_DATA,0xfe);
        sleep(2000);
        outb(PIC_MASTER_DATA,0xfc);
        printf("\n");
    }

    else if(check_input("virtmem") == true)
        virt_mem_example();

    else if(check_input("fcfs") == true)
        fcfs_example();

    else if(check_input("sjf") == true)
        sjf_example();

    else if(check_input("rr") == true)
        rr_example();

    else if(check_input("readsec") == true)
    {
        uint16_t buf[SECTOR_WORDS];
        read_sector(165, buf);

        for(int i = 0; i< SECTOR_WORDS;i++)
            printf("%c ", buf[i]);

        printf("\n");
    }

    else if(check_input("writesec") == true)
    {
        uint16_t buf[SECTOR_WORDS];

        for(int i = 0; i< SECTOR_WORDS;i++)
            buf[i] = 'T';

        write_sector(165, buf);
    }

    else if(check_input("wipesec") == true )
    {
        uint16_t buf[SECTOR_WORDS];

        for(int i = 0; i< SECTOR_WORDS;i++)
            buf[i] = 0;

        write_sector(165, buf);
    }

    else if (!check_input("\n"))
        printf("Command not found.\n");
}
