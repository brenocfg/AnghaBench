#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t USHORT ;
typedef  int UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  (* inb_handler ) (size_t,int*) ;} ;
struct TYPE_5__ {int (* InB ) (size_t) ;} ;
struct TYPE_6__ {TYPE_1__ VddIoHandlers; int /*<<< orphan*/ * hVdd; TYPE_2__ IoHandlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DPRINT (char*,size_t) ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 TYPE_3__* IoPortProc ; 
 size_t MAXWORD ; 
 int stub1 (size_t) ; 
 int /*<<< orphan*/  stub2 (size_t,int*) ; 

UCHAR
IOReadB(USHORT Port)
{
    if (IoPortProc[Port].hVdd == INVALID_HANDLE_VALUE &&
        IoPortProc[Port].IoHandlers.InB)
    {
        return IoPortProc[Port].IoHandlers.InB(Port);
    }
    else if (IoPortProc[Port].hVdd != NULL && IoPortProc[Port].hVdd != INVALID_HANDLE_VALUE &&
             IoPortProc[Port].VddIoHandlers.inb_handler)
    {
        UCHAR Data;
        ASSERT(Port <= MAXWORD);
        IoPortProc[Port].VddIoHandlers.inb_handler(Port, &Data);
        return Data;
    }
    else
    {
        /* Return an empty port byte value */
        DPRINT("Read from unknown port: 0x%X\n", Port);
        return 0xFF;
    }
}