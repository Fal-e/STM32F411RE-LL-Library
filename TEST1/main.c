/*----------------------------------------------------------------------------
 *      main Template for CMSIS RTE C/C++ Project
 *----------------------------------------------------------------------------
 *      Name:    main.c
 *      Purpose: Generic main program body including main() function
 *      Rev.:    1.0.0
 *----------------------------------------------------------------------------*/
/*******************************************************************************
* Copyright (c) 2015 ARM Ltd. and others
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the Eclipse Public License v1.0
* which accompanies this distribution, and is available at
* http://www.eclipse.org/legal/epl-v10.html
*
* Contributors:
* ARM Ltd and ARM Germany GmbH - file template
*******************************************************************************/
#ifndef _VVC_MAIN_H
#define _VVC_MAIN_H
#include <stdint.h>

// Define GPIOB pin mappings for our LED and button.
#define BUTTON_PIN (1)
#define LED_PIN    (3)
#endif
#ifdef _RTE_
  #include "RTE_Components.h"             // Component selection
#endif
#ifdef RTE_CMSIS_RTOS                     // when RTE component CMSIS RTOS is used
  #include "cmsis_os.h"                   // CMSIS RTOS header file
#endif

/* main function */
int main(void)
{

#ifdef RTE_CMSIS_RTOS                   // when using CMSIS RTOS
  osKernelInitialize ();                // initialize CMSIS-RTOS
#endif

  /* Initialize device HAL here */
  
#ifdef RTE_CMSIS_RTOS                   // when using CMSIS RTOS
  // create 'thread' functions that start executing,
  // example: tid_name = osThreadCreate (osThread(name), NULL);
  osKernelStart ();                     // start thread execution 
#endif

  /* Infinite loop */
  while (1)
  {

	  GPIOB->MODER  &= ~(0x3 << (BUTTON_PIN*2));
   /* Add application code here */
  }

}

