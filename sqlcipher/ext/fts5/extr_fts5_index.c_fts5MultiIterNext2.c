#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ rc; } ;
struct TYPE_20__ {int bSkipEmpty; TYPE_2__* aSeg; TYPE_1__* aFirst; } ;
struct TYPE_19__ {scalar_t__ pLeaf; int /*<<< orphan*/  (* xNext ) (TYPE_4__*,TYPE_2__*,int*) ;} ;
struct TYPE_18__ {int iFirst; } ;
typedef  TYPE_2__ Fts5SegIter ;
typedef  TYPE_3__ Fts5Iter ;
typedef  TYPE_4__ Fts5Index ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5AssertMultiIterSetup (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ fts5MultiIterAdvanceRowid (TYPE_3__*,int,TYPE_2__**) ; 
 int /*<<< orphan*/  fts5MultiIterAdvanced (TYPE_4__*,TYPE_3__*,int,int) ; 
 scalar_t__ fts5MultiIterIsEmpty (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  fts5MultiIterSetEof (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_2__*,int*) ; 

__attribute__((used)) static void fts5MultiIterNext2(
  Fts5Index *p, 
  Fts5Iter *pIter,
  int *pbNewTerm                  /* OUT: True if *might* be new term */
){
  assert( pIter->bSkipEmpty );
  if( p->rc==SQLITE_OK ){
    *pbNewTerm = 0;
    do{
      int iFirst = pIter->aFirst[1].iFirst;
      Fts5SegIter *pSeg = &pIter->aSeg[iFirst];
      int bNewTerm = 0;

      assert( p->rc==SQLITE_OK );
      pSeg->xNext(p, pSeg, &bNewTerm);
      if( pSeg->pLeaf==0 || bNewTerm 
       || fts5MultiIterAdvanceRowid(pIter, iFirst, &pSeg)
      ){
        fts5MultiIterAdvanced(p, pIter, iFirst, 1);
        fts5MultiIterSetEof(pIter);
        *pbNewTerm = 1;
      }
      fts5AssertMultiIterSetup(p, pIter);

    }while( fts5MultiIterIsEmpty(p, pIter) );
  }
}