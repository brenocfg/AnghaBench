#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_17__ {scalar_t__ szLeaf; int /*<<< orphan*/  nn; int /*<<< orphan*/  p; } ;
struct TYPE_14__ {int bEof; } ;
struct TYPE_16__ {int bRev; TYPE_2__ base; TYPE_1__* aFirst; TYPE_3__* aSeg; } ;
struct TYPE_15__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  iEndofDoclist; int /*<<< orphan*/  iRowid; int /*<<< orphan*/  iLeafOffset; TYPE_5__* pLeaf; } ;
struct TYPE_13__ {int iFirst; } ;
typedef  TYPE_3__ Fts5SegIter ;
typedef  TYPE_4__ Fts5Iter ;
typedef  int /*<<< orphan*/  Fts5Index ;
typedef  TYPE_5__ Fts5Data ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_SEGITER_ONETERM ; 
 int /*<<< orphan*/  FTS5_SEGITER_REVERSE ; 
 int /*<<< orphan*/  fts5DataRelease (TYPE_5__*) ; 
 int /*<<< orphan*/  fts5GetVarint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* fts5MultiIterAlloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fts5SegIterLoadNPos (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  fts5SegIterReverseInitPage (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  fts5SegIterSetNext (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void fts5MultiIterNew2(
  Fts5Index *p,                   /* FTS5 backend to iterate within */
  Fts5Data *pData,                /* Doclist to iterate through */
  int bDesc,                      /* True for descending rowid order */
  Fts5Iter **ppOut                /* New object */
){
  Fts5Iter *pNew;
  pNew = fts5MultiIterAlloc(p, 2);
  if( pNew ){
    Fts5SegIter *pIter = &pNew->aSeg[1];

    pIter->flags = FTS5_SEGITER_ONETERM;
    if( pData->szLeaf>0 ){
      pIter->pLeaf = pData;
      pIter->iLeafOffset = fts5GetVarint(pData->p, (u64*)&pIter->iRowid);
      pIter->iEndofDoclist = pData->nn;
      pNew->aFirst[1].iFirst = 1;
      if( bDesc ){
        pNew->bRev = 1;
        pIter->flags |= FTS5_SEGITER_REVERSE;
        fts5SegIterReverseInitPage(p, pIter);
      }else{
        fts5SegIterLoadNPos(p, pIter);
      }
      pData = 0;
    }else{
      pNew->base.bEof = 1;
    }
    fts5SegIterSetNext(p, pIter);

    *ppOut = pNew;
  }

  fts5DataRelease(pData);
}