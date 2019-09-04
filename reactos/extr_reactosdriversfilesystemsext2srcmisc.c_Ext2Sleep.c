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
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {int QuadPart; } ;
typedef  int LONGLONG ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  KeDelayExecutionThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  TRUE ; 

VOID
Ext2Sleep(ULONG ms)
{
    LARGE_INTEGER Timeout;
    Timeout.QuadPart = (LONGLONG)ms*1000*(-10); /* ms/1000 sec*/
    KeDelayExecutionThread(KernelMode, TRUE, &Timeout);
}