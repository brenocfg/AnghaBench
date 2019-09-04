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
struct list {int dummy; } ;
struct frame_node {int /*<<< orphan*/  entry; TYPE_1__* frame; } ;
struct TYPE_3__ {int /*<<< orphan*/  pFrameFirstChild; } ;
typedef  TYPE_1__ D3DXFRAME ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct frame_node* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  list_add_tail (struct list*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL queue_frame_node(struct list *queue, D3DXFRAME *frame)
{
    struct frame_node *node;

    if (!frame->pFrameFirstChild)
        return TRUE;

    node = HeapAlloc(GetProcessHeap(), 0, sizeof(*node));
    if (!node)
        return FALSE;

    node->frame = frame;
    list_add_tail(queue, &node->entry);

    return TRUE;
}