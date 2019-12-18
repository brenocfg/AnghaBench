#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/ * p; } ;
struct TYPE_17__ {TYPE_1__* pConfig; } ;
struct TYPE_14__ {scalar_t__ nData; int /*<<< orphan*/ * pData; int /*<<< orphan*/  iRowid; } ;
struct TYPE_16__ {scalar_t__ pColset; TYPE_8__ poslist; TYPE_3__ base; TYPE_6__* pIndex; } ;
struct TYPE_15__ {scalar_t__ nPos; size_t iLeafOffset; TYPE_2__* pLeaf; int /*<<< orphan*/  iRowid; } ;
struct TYPE_13__ {scalar_t__ szLeaf; int /*<<< orphan*/ * p; } ;
struct TYPE_12__ {scalar_t__ eDetail; } ;
typedef  TYPE_4__ Fts5SegIter ;
typedef  TYPE_5__ Fts5Iter ;

/* Variables and functions */
 scalar_t__ FTS5_DETAIL_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5BufferZero (TYPE_8__*) ; 
 int /*<<< orphan*/  fts5SegiterPoslist (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ,TYPE_8__*) ; 

__attribute__((used)) static void fts5IterSetOutputs_Nocolset(Fts5Iter *pIter, Fts5SegIter *pSeg){
  pIter->base.iRowid = pSeg->iRowid;
  pIter->base.nData = pSeg->nPos;

  assert( pIter->pIndex->pConfig->eDetail!=FTS5_DETAIL_NONE );
  assert( pIter->pColset==0 );

  if( pSeg->iLeafOffset+pSeg->nPos<=pSeg->pLeaf->szLeaf ){
    /* All data is stored on the current page. Populate the output 
    ** variables to point into the body of the page object. */
    pIter->base.pData = &pSeg->pLeaf->p[pSeg->iLeafOffset];
  }else{
    /* The data is distributed over two or more pages. Copy it into the
    ** Fts5Iter.poslist buffer and then set the output pointer to point
    ** to this buffer.  */
    fts5BufferZero(&pIter->poslist);
    fts5SegiterPoslist(pIter->pIndex, pSeg, 0, &pIter->poslist);
    pIter->base.pData = pIter->poslist.p;
  }
}