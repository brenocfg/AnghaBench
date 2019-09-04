#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_t ;
struct TYPE_6__ {TYPE_3__* pending_window; int /*<<< orphan*/  window; } ;
typedef  TYPE_2__ start_doc_binding_task_t ;
struct TYPE_8__ {int /*<<< orphan*/  mon; } ;
struct TYPE_7__ {TYPE_1__* bscallback; } ;
struct TYPE_5__ {TYPE_4__ bsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDING_NAVIGATED ; 
 int /*<<< orphan*/  set_current_mon (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_binding (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void start_doc_binding_proc(task_t *_task)
{
    start_doc_binding_task_t *task = (start_doc_binding_task_t*)_task;

    set_current_mon(task->window, task->pending_window->bscallback->bsc.mon, BINDING_NAVIGATED);
    start_binding(task->pending_window, &task->pending_window->bscallback->bsc, NULL);
}