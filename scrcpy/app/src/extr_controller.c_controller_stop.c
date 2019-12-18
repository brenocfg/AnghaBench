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
struct controller {int stopped; int /*<<< orphan*/  mutex; int /*<<< orphan*/  msg_cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 

void
controller_stop(struct controller *controller) {
    mutex_lock(controller->mutex);
    controller->stopped = true;
    cond_signal(controller->msg_cond);
    mutex_unlock(controller->mutex);
}