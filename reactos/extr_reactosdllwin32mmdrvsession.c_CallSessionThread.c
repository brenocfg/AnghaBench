#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ThreadFunction ;
struct TYPE_5__ {int /*<<< orphan*/  result; int /*<<< orphan*/  ready_event; int /*<<< orphan*/  go_event; int /*<<< orphan*/  parameter; int /*<<< orphan*/  function; } ;
struct TYPE_6__ {TYPE_1__ thread; } ;
typedef  TYPE_2__ SessionInfo ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  MMRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_2__*) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

MMRESULT
CallSessionThread(
    SessionInfo* session_info,
    ThreadFunction function,
    PVOID thread_parameter)
{
    ASSERT(session_info);

    session_info->thread.function = function;
    session_info->thread.parameter = thread_parameter;

    DPRINT("Calling session thread\n");
    SetEvent(session_info->thread.go_event);

    DPRINT("Waiting for thread response\n");
    WaitForSingleObject(session_info->thread.ready_event, INFINITE);

    return session_info->thread.result;
}