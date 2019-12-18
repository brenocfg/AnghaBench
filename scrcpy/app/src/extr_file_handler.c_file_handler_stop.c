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
struct file_handler {int stopped; scalar_t__ current_process; int /*<<< orphan*/  mutex; int /*<<< orphan*/  event_cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGW (char*) ; 
 scalar_t__ PROCESS_NONE ; 
 int /*<<< orphan*/  cmd_simple_wait (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmd_terminate (scalar_t__) ; 
 int /*<<< orphan*/  cond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 

void
file_handler_stop(struct file_handler *file_handler) {
    mutex_lock(file_handler->mutex);
    file_handler->stopped = true;
    cond_signal(file_handler->event_cond);
    if (file_handler->current_process != PROCESS_NONE) {
        if (!cmd_terminate(file_handler->current_process)) {
            LOGW("Could not terminate install process");
        }
        cmd_simple_wait(file_handler->current_process, NULL);
        file_handler->current_process = PROCESS_NONE;
    }
    mutex_unlock(file_handler->mutex);
}