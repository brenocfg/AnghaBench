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
typedef  int /*<<< orphan*/  task_proc_t ;
struct TYPE_5__ {int /*<<< orphan*/  entry; int /*<<< orphan*/  destr; int /*<<< orphan*/  proc; } ;
typedef  TYPE_1__ task_header_t ;
typedef  int /*<<< orphan*/  task_destr_t ;
struct TYPE_6__ {int /*<<< orphan*/  frame_hwnd; int /*<<< orphan*/  task_queue; } ;
typedef  TYPE_2__ DocHost ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  PostMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_DOCHOSTTASK ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

void push_dochost_task(DocHost *This, task_header_t *task, task_proc_t proc, task_destr_t destr, BOOL send)
{
    BOOL is_empty;

    task->proc = proc;
    task->destr = destr;

    is_empty = list_empty(&This->task_queue);
    list_add_tail(&This->task_queue, &task->entry);

    if(send)
        SendMessageW(This->frame_hwnd, WM_DOCHOSTTASK, 0, 0);
    else if(is_empty)
        PostMessageW(This->frame_hwnd, WM_DOCHOSTTASK, 0, 0);
}