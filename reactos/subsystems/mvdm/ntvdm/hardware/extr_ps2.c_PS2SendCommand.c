#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  Param; int /*<<< orphan*/  (* DeviceCommand ) (int /*<<< orphan*/ ,size_t) ;int /*<<< orphan*/  IsEnabled; } ;
typedef  TYPE_1__* PPS2_PORT ;
typedef  size_t BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ControllerConfig ; 
 int /*<<< orphan*/  PS2_CONFIG_AUX_DISABLE ; 
 int /*<<< orphan*/  PS2_CONFIG_KBD_DISABLE ; 
 size_t PS2_PORTS ; 
 TYPE_1__* Ports ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static VOID PS2SendCommand(BYTE PS2Port, BYTE Command)
{
    PPS2_PORT Port;

    ASSERT(PS2Port < PS2_PORTS);
    Port = &Ports[PS2Port];

    /*
     * According to http://www.win.tue.nl/~aeb/linux/kbd/scancodes-11.html#kccad
     * any PS/2 command sent reenables the corresponding port.
     */
    if (PS2Port == 0)
        ControllerConfig &= ~PS2_CONFIG_KBD_DISABLE;
    else // if (PS2Port == 1)
        ControllerConfig &= ~PS2_CONFIG_AUX_DISABLE;

    Port->IsEnabled = TRUE;

    /* Call the device command */
    if (Port->DeviceCommand) Port->DeviceCommand(Port->Param, Command);
}