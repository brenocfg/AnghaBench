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
struct TYPE_4__ {int nSeg; int /*<<< orphan*/  xSetOutputs; int /*<<< orphan*/ * pIndex; int /*<<< orphan*/ * aSeg; int /*<<< orphan*/ * aFirst; } ;
typedef  int /*<<< orphan*/  Fts5SegIter ;
typedef  TYPE_1__ Fts5Iter ;
typedef  int /*<<< orphan*/  Fts5Index ;
typedef  int /*<<< orphan*/  Fts5CResult ;

/* Variables and functions */
 TYPE_1__* fts5IdxMalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fts5IterSetOutputs_Noop ; 

__attribute__((used)) static Fts5Iter *fts5MultiIterAlloc(
  Fts5Index *p,                   /* FTS5 backend to iterate within */
  int nSeg
){
  Fts5Iter *pNew;
  int nSlot;                      /* Power of two >= nSeg */

  for(nSlot=2; nSlot<nSeg; nSlot=nSlot*2);
  pNew = fts5IdxMalloc(p, 
      sizeof(Fts5Iter) +                  /* pNew */
      sizeof(Fts5SegIter) * (nSlot-1) +   /* pNew->aSeg[] */
      sizeof(Fts5CResult) * nSlot         /* pNew->aFirst[] */
  );
  if( pNew ){
    pNew->nSeg = nSlot;
    pNew->aFirst = (Fts5CResult*)&pNew->aSeg[nSlot];
    pNew->pIndex = p;
    pNew->xSetOutputs = fts5IterSetOutputs_Noop;
  }
  return pNew;
}