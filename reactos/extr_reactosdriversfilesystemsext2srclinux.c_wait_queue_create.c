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
struct __wait_queue {int /*<<< orphan*/  event; int /*<<< orphan*/  task_list; void* private; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ KeGetCurrentThread () ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SynchronizationEvent ; 
 int /*<<< orphan*/  WQ_FLAG_AUTO_REMOVAL ; 
 struct __wait_queue* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct __wait_queue*,int /*<<< orphan*/ ,int) ; 

struct __wait_queue *
wait_queue_create()
{
    struct __wait_queue * wait = NULL;
    wait = kmalloc(sizeof(struct __wait_queue), GFP_KERNEL);
    if (!wait) {
        return NULL;
    }

    memset(wait, 0, sizeof(struct __wait_queue));
    wait->flags = WQ_FLAG_AUTO_REMOVAL;
    wait->private = (void *)KeGetCurrentThread();
    INIT_LIST_HEAD(&wait->task_list);
    KeInitializeEvent(&(wait->event),
                      SynchronizationEvent,
                      FALSE);

    return wait;
}