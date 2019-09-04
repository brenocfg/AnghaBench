#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* keys; struct TYPE_4__* order; int /*<<< orphan*/ * heap; } ;
typedef  TYPE_1__ PriorityQ ;

/* Variables and functions */
 int /*<<< orphan*/  __gl_pqHeapDeletePriorityQ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memFree (TYPE_1__*) ; 

void pqDeletePriorityQ( PriorityQ *pq )
{
  assert(pq != NULL); 
  if (pq->heap != NULL) __gl_pqHeapDeletePriorityQ( pq->heap );
  if (pq->order != NULL) memFree( pq->order );
  if (pq->keys != NULL) memFree( pq->keys );
  memFree( pq );
}