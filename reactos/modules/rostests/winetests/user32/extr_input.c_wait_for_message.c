#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ message; } ;
typedef  TYPE_1__ MSG ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DispatchMessageA (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MsgWaitForMultipleObjects (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 scalar_t__ PeekMessageA (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QS_ALLINPUT ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WM_PAINT ; 

__attribute__((used)) static BOOL wait_for_message( MSG *msg )
{
    BOOL ret;

    for (;;)
    {
        ret = PeekMessageA(msg, 0, 0, 0, PM_REMOVE);
        if (ret)
        {
            if (msg->message == WM_PAINT) DispatchMessageA(msg);
            else break;
        }
        else if (MsgWaitForMultipleObjects(0, NULL, FALSE, 100, QS_ALLINPUT) == WAIT_TIMEOUT) break;
    }
    if (!ret) msg->message = 0;
    return ret;
}