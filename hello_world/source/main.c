/*
 * Copyright 2016-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    hello_world.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "main.h"
#include "fsl_gpio.h"
/* TODO: insert other definitions and declarations here. */

/*------------------------- Private Function Prototypes ----------------------*/
static void Led_Init( void );
static void Led_Mng( void );
/*
 * @brief   Application entry point.
 */
int main(void)
{
  /* Init board hardware. */
  BOARD_ConfigMPU();
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
  /* Init FSL debug console. */
  BOARD_InitDebugConsole();
#endif

  Led_Init();
  PRINTF("LED Toggle Program\r\n");

  while(1)
  {
    // SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    Led_Mng();
  }

  return 0 ;
}

/*------------------------ Private Function Definitions ----------------------*/
static void Led_Init( void )
{
  gpio_pin_config_t led_config =
  {
      kGPIO_DigitalOutput,
      0,
      kGPIO_NoIntmode
  };

  GPIO_PinInit(USER_LED_GPIO, USER_LED_GPIO_PIN, &led_config);
}

static void Led_Mng( void )
{
  static uint8_t led_state = false;
  if( led_state )
  {
    led_state = false;
    GPIO_PinWrite(USER_LED_GPIO, USER_LED_GPIO_PIN, 0);
  }
  else
  {
    led_state = true;
    GPIO_PinWrite(USER_LED_GPIO, USER_LED_GPIO_PIN, 1);
  }
}

/*------------------------- Public Function Definitions ----------------------*/
