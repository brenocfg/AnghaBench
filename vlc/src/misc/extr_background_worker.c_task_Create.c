#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task {void* entity; int /*<<< orphan*/  timeout; void* id; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pf_hold ) (void*) ;int /*<<< orphan*/  default_timeout; } ;
struct background_worker {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 struct task* malloc (int) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct task *task_Create(struct background_worker *worker, void *id,
                                void *entity, int timeout)
{
    struct task *task = malloc(sizeof(*task));
    if (unlikely(!task))
        return NULL;

    task->id = id;
    task->entity = entity;
    task->timeout = timeout < 0 ? worker->conf.default_timeout : VLC_TICK_FROM_MS(timeout);
    worker->conf.pf_hold(task->entity);
    return task;
}