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
struct udev_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDEV_CTRL_START_EXEC_QUEUE ; 
 int udev_ctrl_send (struct udev_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int udev_ctrl_send_start_exec_queue(struct udev_ctrl *uctrl) {
        return udev_ctrl_send(uctrl, UDEV_CTRL_START_EXEC_QUEUE, 0, NULL);
}