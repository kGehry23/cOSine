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
#include "../libc/stdio/stdio.h"
#include "../kernel/tty/terminal.h"
#include "../drivers/ps2/keyboard/keyboard_api.h"
#include "../drivers/disk/ata/ata.h"
#include "../drivers/pit/pit.h"
#include "../cpu/scheduling/scheduler.h"
#include "../cpu/dispatcher/dispatcher.h"


/************************************
 * STATIC AND GLOBAL VARIABLES
 ************************************/

//Buffer for previously entered commands
static char* cmd_arr[128];

task shell;
static task t1;
static task t2;
extern task* current_task;

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
static void print_shell_prompt(void)
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
        sleep(EXAMPLE_TIME_QUANTUM);
        current_task->execution_time = current_task->execution_time - EXAMPLE_TIME_QUANTUM;

        //If the task has completed, print a message
        if(current_task->execution_time <= 0)
        {
            printf("Task %d Complete ", current_task->tid);
            current_task->state = TERMINATED;
        }

        printf("\n");
        dispatch(current_task, current_task->next_task);
    }
}

/*!
 * @brief Echos the input entered back to the user
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
 * @brief Echos the input entered back to the user
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
 * @brief Echos the input entered back to the user
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

    printf("Execution times (milliseconds): \nTask %d: %d\n", t1.tid, t1.execution_time);
    printf("Task %d: %d\n", t2.tid, t2.execution_time);
    printf("Task %d: %d\n", t3.tid, t3.execution_time);
    printf("Task %d: %d\n\n", t4.tid, t4.execution_time);

    task task_queue[4] = {t1, t2, t3, t4};

    rr_sched(task_queue, 4);
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
    }

    else if(check_input("fcfs") == true)
        fcfs_example();

    else if(check_input("sjf") == true)
        sjf_example();

    else if(check_input("rr") == true)
        rr_example();

    else if(check_input("readsec") == true )
    {
        uint16_t buf[SECTOR_WORDS];
        read_sector(165, buf);

        for(int i = 0; i< SECTOR_WORDS;i++)
            printf("%c ", buf[i]);

        printf("\n");
    }

    else if(check_input("writesec") == true )
    {
        uint16_t buf[SECTOR_WORDS];

        for(int i = 0; i< SECTOR_WORDS;i++)
            buf[i] = 'T';

        write_sector(165, buf);
    }

    else if (!check_input("\n"))
        printf("Command not found.\n");
}


