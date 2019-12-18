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
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  (* inw_handler ) (size_t,size_t*) ;} ;
struct TYPE_5__ {size_t (* InW ) (size_t) ;} ;
struct TYPE_6__ {TYPE_1__ VddIoHandlers; int /*<<< orphan*/ * hVdd; TYPE_2__ IoHandlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IOReadB (size_t) ; 
 TYPE_3__* IoPortProc ; 
 size_t MAKEWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MAXWORD ; 
 size_t stub1 (size_t) ; 
 int /*<<< orphan*/  stub2 (size_t,size_t*) ; 

USHORT
IOReadW(USHORT Port)
{
    if (IoPortProc[Port].hVdd == INVALID_HANDLE_VALUE &&
        IoPortProc[Port].IoHandlers.InW)
    {
        return IoPortProc[Port].IoHandlers.InW(Port);
    }
    else if (IoPortProc[Port].hVdd != NULL && IoPortProc[Port].hVdd != INVALID_HANDLE_VALUE &&
             IoPortProc[Port].VddIoHandlers.inw_handler)
    {
        USHORT Data;
        ASSERT(Port <= MAXWORD);
        IoPortProc[Port].VddIoHandlers.inw_handler(Port, &Data);
        return Data;
    }
    else
    {
        UCHAR Low, High;

        // FIXME: Is it ok on Little endian and Big endian ??
        Low  = IOReadB(Port);
        High = IOReadB(Port + sizeof(UCHAR));
        return MAKEWORD(Low, High);
    }
}