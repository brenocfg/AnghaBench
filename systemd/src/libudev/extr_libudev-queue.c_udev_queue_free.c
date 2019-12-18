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
struct udev_queue {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct udev_queue*) ; 
 struct udev_queue* mfree (struct udev_queue*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct udev_queue *udev_queue_free(struct udev_queue *udev_queue) {
        assert(udev_queue);

        safe_close(udev_queue->fd);
        return mfree(udev_queue);
}