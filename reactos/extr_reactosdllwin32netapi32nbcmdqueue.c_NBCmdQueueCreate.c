#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* DebugInfo; } ;
struct NBCmdQueue {int /*<<< orphan*/ * head; TYPE_2__ cs; int /*<<< orphan*/ * heap; } ;
struct TYPE_3__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/ * GetProcessHeap () ; 
 struct NBCmdQueue* HeapAlloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_2__*) ; 

struct NBCmdQueue *NBCmdQueueCreate(HANDLE heap)
{
    struct NBCmdQueue *queue;

    if (heap == NULL)
        heap = GetProcessHeap();
    queue = HeapAlloc(heap, 0, sizeof(struct NBCmdQueue));
    if (queue)
    {
        queue->heap = heap;
        InitializeCriticalSection(&queue->cs);
        queue->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": NBCmdQueue.cs");
        queue->head = NULL;
    }
    return queue;
}