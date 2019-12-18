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
struct TYPE_3__ {scalar_t__ error; scalar_t__ state; } ;
typedef  TYPE_1__ HttpTxTask ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_TASK_RT_STATE_FINISHED ; 
 scalar_t__ HTTP_TASK_STATE_CANCELED ; 
 scalar_t__ HTTP_TASK_STATE_ERROR ; 
 scalar_t__ HTTP_TASK_STATE_FINISHED ; 
 scalar_t__ SYNC_ERROR_ID_NO_ERROR ; 
 int /*<<< orphan*/  transition_state (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
http_upload_done (void *vdata)
{
    HttpTxTask *task = vdata;

    if (task->error != SYNC_ERROR_ID_NO_ERROR)
        transition_state (task, HTTP_TASK_STATE_ERROR, HTTP_TASK_RT_STATE_FINISHED);
    else if (task->state == HTTP_TASK_STATE_CANCELED)
        transition_state (task, task->state, HTTP_TASK_RT_STATE_FINISHED);
    else
        transition_state (task, HTTP_TASK_STATE_FINISHED, HTTP_TASK_RT_STATE_FINISHED);
}