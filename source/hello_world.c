/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * Demonstrate the use of ITM_Print:
 * configure in IDE on SWO Trace Config:
 *     Core Clock Speed [Hz}: 996000000   (or use "Detect")
 *     Trace Clock Speed [Hz]: 132000000
 * "SWO configured by IDE" - enable!
 * enable (run) the SWO ITM Console
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

int _write(int iFileHandle, char *pcBuffer, int iLength);
int _read(int iFileHandle, char *pcBuffer, int iLength);

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    char ch;
    char inBuf[10];
    int i;

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("hello world.\r\n");

    ch = 'A';

    while (1)
    {
        ////ch = GETCHAR();
        PUTCHAR(ch);
        ch++;
        if (ch == 'z')
        	ch = 'A';

        i = _read(0, inBuf, 1);
        /* this is blocking until something was received, it is buffered,
         * so entering several characters returns each single one in this loop
         */
        if (i)
        {
        	inBuf[1] = '\r';
        	inBuf[2] = '\n';
        	_write(1, inBuf, 3);
        }

        _write(1, "Hi!\r\n", 5);

        SDK_DelayAtLeastUs(500000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
}
