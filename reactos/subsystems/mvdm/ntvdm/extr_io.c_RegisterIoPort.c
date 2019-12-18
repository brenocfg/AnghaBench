#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t USHORT ;
struct TYPE_3__ {int /*<<< orphan*/ * OutB; int /*<<< orphan*/ * InB; } ;
struct TYPE_4__ {int /*<<< orphan*/  hVdd; TYPE_1__ IoHandlers; } ;
typedef  int /*<<< orphan*/ * EMULATOR_OUTB_PROC ;
typedef  int /*<<< orphan*/ * EMULATOR_INB_PROC ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,size_t) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 TYPE_2__* IoPortProc ; 

VOID RegisterIoPort(USHORT Port,
                    EMULATOR_INB_PROC  InHandler,
                    EMULATOR_OUTB_PROC OutHandler)
{
    if (IoPortProc[Port].IoHandlers.InB == NULL)
        IoPortProc[Port].IoHandlers.InB = InHandler;
    else
        DPRINT1("IoPortProc[0x%X].IoHandlers.InB already registered\n", Port);

    if (IoPortProc[Port].IoHandlers.OutB == NULL)
        IoPortProc[Port].IoHandlers.OutB = OutHandler;
    else
        DPRINT1("IoPortProc[0x%X].IoHandlers.OutB already registered\n", Port);

    /* We hold the I/O port internally */
    IoPortProc[Port].hVdd = INVALID_HANDLE_VALUE;
}