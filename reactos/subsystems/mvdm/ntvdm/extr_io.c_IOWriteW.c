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
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t USHORT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  (* outw_handler ) (size_t,size_t) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* OutW ) (size_t,size_t) ;} ;
struct TYPE_6__ {TYPE_1__ VddIoHandlers; int /*<<< orphan*/ * hVdd; TYPE_2__ IoHandlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  HIBYTE (size_t) ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IOWriteB (size_t,int /*<<< orphan*/ ) ; 
 TYPE_3__* IoPortProc ; 
 int /*<<< orphan*/  LOBYTE (size_t) ; 
 size_t MAXWORD ; 
 int /*<<< orphan*/  stub1 (size_t,size_t) ; 
 int /*<<< orphan*/  stub2 (size_t,size_t) ; 

VOID
IOWriteW(USHORT Port,
         USHORT Buffer)
{
    if (IoPortProc[Port].hVdd == INVALID_HANDLE_VALUE &&
        IoPortProc[Port].IoHandlers.OutW)
    {
        IoPortProc[Port].IoHandlers.OutW(Port, Buffer);
    }
    else if (IoPortProc[Port].hVdd != NULL && IoPortProc[Port].hVdd != INVALID_HANDLE_VALUE &&
             IoPortProc[Port].VddIoHandlers.outw_handler)
    {
        ASSERT(Port <= MAXWORD);
        IoPortProc[Port].VddIoHandlers.outw_handler(Port, Buffer);
    }
    else
    {
        // FIXME: Is it ok on Little endian and Big endian ??
        IOWriteB(Port, LOBYTE(Buffer));
        IOWriteB(Port + sizeof(UCHAR), HIBYTE(Buffer));
    }
}