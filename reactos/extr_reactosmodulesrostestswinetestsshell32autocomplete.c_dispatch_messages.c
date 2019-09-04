#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MSG ;

/* Variables and functions */
 int /*<<< orphan*/  DispatchMessageA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 scalar_t__ PeekMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  TranslateMessage (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispatch_messages(void)
{
    MSG msg;
    Sleep(33);
    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}