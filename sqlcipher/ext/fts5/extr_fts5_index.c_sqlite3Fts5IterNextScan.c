#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ rc; } ;
struct TYPE_12__ {int bEof; } ;
struct TYPE_14__ {TYPE_6__* pIndex; TYPE_3__ base; TYPE_1__* aFirst; TYPE_4__* aSeg; } ;
struct TYPE_11__ {scalar_t__* p; } ;
struct TYPE_13__ {scalar_t__ pLeaf; TYPE_2__ term; } ;
struct TYPE_10__ {size_t iFirst; } ;
typedef  TYPE_4__ Fts5SegIter ;
typedef  TYPE_5__ Fts5Iter ;
typedef  int /*<<< orphan*/  Fts5IndexIter ;
typedef  TYPE_6__ Fts5Index ;

/* Variables and functions */
 scalar_t__ FTS5_MAIN_PREFIX ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5DataRelease (scalar_t__) ; 
 int fts5IndexReturn (TYPE_6__*) ; 
 int /*<<< orphan*/  fts5MultiIterNext (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sqlite3Fts5IterNextScan(Fts5IndexIter *pIndexIter){
  Fts5Iter *pIter = (Fts5Iter*)pIndexIter;
  Fts5Index *p = pIter->pIndex;

  assert( pIter->pIndex->rc==SQLITE_OK );

  fts5MultiIterNext(p, pIter, 0, 0);
  if( p->rc==SQLITE_OK ){
    Fts5SegIter *pSeg = &pIter->aSeg[ pIter->aFirst[1].iFirst ];
    if( pSeg->pLeaf && pSeg->term.p[0]!=FTS5_MAIN_PREFIX ){
      fts5DataRelease(pSeg->pLeaf);
      pSeg->pLeaf = 0;
      pIter->base.bEof = 1;
    }
  }

  return fts5IndexReturn(pIter->pIndex);
}