/********************************************************************************
 * @file    shell.h
 * 
 * @author  Kai Gehry
 * @date    2026-01-18
 *
 * @brief   Header for cOSine shell (cOSh -> hyperbolic cos)
 * 
 ********************************************************************************
*/

/************************************
 * INCLUDES
 ************************************/
#include <stdbool.h>
#include "../io/io.h"


/************************************
 * MACROS
 ************************************/
#define SHELL_PROMPT_FG     12
#define SHELL_FG            7
#define SHELL_BG            0


/************************************
 * FUNCTION PROTOTYPES
 ************************************/

/*!
 * @brief Initializes and starts cOSh
 * @return None
 */
void shell_init(void);