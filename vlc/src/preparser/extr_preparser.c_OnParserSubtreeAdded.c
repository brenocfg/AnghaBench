#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* req; } ;
typedef  TYPE_2__ input_preparser_task_t ;
struct TYPE_6__ {int /*<<< orphan*/  userdata; int /*<<< orphan*/  item; TYPE_1__* cbs; } ;
typedef  TYPE_3__ input_preparser_req_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* on_subtree_added ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void OnParserSubtreeAdded(input_item_t *item, input_item_node_t *subtree,
                                 void *task_)
{
    VLC_UNUSED(item);
    input_preparser_task_t* task = task_;
    input_preparser_req_t *req = task->req;

    if (req->cbs && req->cbs->on_subtree_added)
        req->cbs->on_subtree_added(req->item, subtree, req->userdata);
}