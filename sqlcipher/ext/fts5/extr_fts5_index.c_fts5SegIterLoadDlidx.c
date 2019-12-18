#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ szLeaf; } ;
struct TYPE_6__ {int flags; scalar_t__ iEndofDoclist; int /*<<< orphan*/  iTermLeafPgno; int /*<<< orphan*/  pDlidx; int /*<<< orphan*/  iLeafPgno; TYPE_3__* pLeaf; TYPE_1__* pSeg; } ;
struct TYPE_5__ {int iSegid; } ;
typedef  TYPE_2__ Fts5SegIter ;
typedef  int /*<<< orphan*/  Fts5Index ;
typedef  TYPE_3__ Fts5Data ;

/* Variables and functions */
 int FTS5_SEGITER_ONETERM ; 
 int FTS5_SEGITER_REVERSE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5DlidxIterInit (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fts5SegIterLoadDlidx(Fts5Index *p, Fts5SegIter *pIter){
  int iSeg = pIter->pSeg->iSegid;
  int bRev = (pIter->flags & FTS5_SEGITER_REVERSE);
  Fts5Data *pLeaf = pIter->pLeaf; /* Current leaf data */

  assert( pIter->flags & FTS5_SEGITER_ONETERM );
  assert( pIter->pDlidx==0 );

  /* Check if the current doclist ends on this page. If it does, return
  ** early without loading the doclist-index (as it belongs to a different
  ** term. */
  if( pIter->iTermLeafPgno==pIter->iLeafPgno 
   && pIter->iEndofDoclist<pLeaf->szLeaf 
  ){
    return;
  }

  pIter->pDlidx = fts5DlidxIterInit(p, bRev, iSeg, pIter->iTermLeafPgno);
}