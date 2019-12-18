#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ rc; } ;
struct TYPE_10__ {int nSeg; TYPE_1__* aSeg; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* xNext ) (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ Fts5SegIter ;
typedef  TYPE_2__ Fts5Iter ;
typedef  TYPE_3__ Fts5Index ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts5MultiIterDoCompare (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fts5MultiIterAdvanced(
  Fts5Index *p,                   /* FTS5 backend to iterate within */
  Fts5Iter *pIter,                /* Iterator to update aFirst[] array for */
  int iChanged,                   /* Index of sub-iterator just advanced */
  int iMinset                     /* Minimum entry in aFirst[] to set */
){
  int i;
  for(i=(pIter->nSeg+iChanged)/2; i>=iMinset && p->rc==SQLITE_OK; i=i/2){
    int iEq;
    if( (iEq = fts5MultiIterDoCompare(pIter, i)) ){
      Fts5SegIter *pSeg = &pIter->aSeg[iEq];
      assert( p->rc==SQLITE_OK );
      pSeg->xNext(p, pSeg, 0);
      i = pIter->nSeg + iEq;
    }
  }
}