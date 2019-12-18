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
struct FiberData {size_t nPrio; size_t nRealPrio; int /*<<< orphan*/  leQueue; scalar_t__ nBoost; int /*<<< orphan*/  nQuantumQueued; int /*<<< orphan*/  pFiber; scalar_t__ bExitPrev; struct FiberData* pfdPrev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFiber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * a_leQueues ; 
 int /*<<< orphan*/  free (struct FiberData*) ; 
 int /*<<< orphan*/  nQuantum ; 
 struct FiberData* pfdLastStarveScan ; 

void Fbt_AfterSwitch(struct FiberData * pfdCur)
{
 struct FiberData * pfdPrev;

 pfdPrev = pfdCur->pfdPrev;

 /* The previous fiber left some homework for us */
 if(pfdPrev)
 {
  /* Kill the predecessor */
  if(pfdCur->bExitPrev)
  {
   if(pfdLastStarveScan == pfdPrev)
    pfdLastStarveScan = 0;

   DeleteFiber(pfdPrev->pFiber);
   free(pfdPrev);
  }
  /* Enqueue the previous fiber in the correct ready queue */
  else
  {
   /* Remember the quantum in which the previous fiber was queued */
   pfdPrev->nQuantumQueued = nQuantum;

   /* Disable the anti-starvation boost */
   if(pfdPrev->nBoost)
   {
    pfdPrev->nBoost = 0;
    pfdPrev->nPrio = pfdPrev->nRealPrio;
   }

   /* Enqueue the previous fiber */
   InsertTailList
   (
    &a_leQueues[pfdPrev->nPrio],
    &pfdPrev->leQueue
   );
  }
 }
}