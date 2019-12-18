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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 scalar_t__* current_event ; 
 int /*<<< orphan*/  event_cs ; 
 int /*<<< orphan*/  event_handle ; 
 int /*<<< orphan*/  ok (int,char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,scalar_t__*) ; 
 int /*<<< orphan*/  trace (char*,char const*) ; 

__attribute__((used)) static void expect_event(const char *event_name)
{
    char evt[32];
    DWORD res;

    trace("waiting for %s\n", event_name);

    res = WaitForSingleObject(event_handle, 30000);
    ok(res == WAIT_OBJECT_0, "WaitForSingleObject failed: %u\n", res);
    if(res != WAIT_OBJECT_0)
        return;

    EnterCriticalSection(&event_cs);
    strcpy(evt, current_event);
    *current_event = 0;
    LeaveCriticalSection(&event_cs);

    ok(!strcmp(evt, event_name), "Unexpected event: %s, expected %s\n", evt, event_name);
}