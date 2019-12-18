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
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_ALL_ACCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OpenEventA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OutputDebugStringA (char*) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static void dummy_process(char *event_name)
{
    HANDLE event = OpenEventA(EVENT_ALL_ACCESS, FALSE, event_name);

    while (TRUE)
    {
        SetEvent(event);
        OutputDebugStringA("test");
        Sleep(5);
    }
}