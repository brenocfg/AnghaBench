#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ eDetail; int nCol; } ;
struct TYPE_8__ {int /*<<< orphan*/  xSetOutputs; int /*<<< orphan*/  poslist; TYPE_2__* pColset; TYPE_1__* pIndex; } ;
struct TYPE_7__ {scalar_t__ nCol; } ;
struct TYPE_6__ {TYPE_4__* pConfig; } ;
typedef  TYPE_3__ Fts5Iter ;
typedef  TYPE_4__ Fts5Config ;

/* Variables and functions */
 scalar_t__ FTS5_DETAIL_COLUMNS ; 
 scalar_t__ FTS5_DETAIL_FULL ; 
 scalar_t__ FTS5_DETAIL_NONE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5IterSetOutputs_Col ; 
 int /*<<< orphan*/  fts5IterSetOutputs_Col100 ; 
 int /*<<< orphan*/  fts5IterSetOutputs_Full ; 
 int /*<<< orphan*/  fts5IterSetOutputs_Nocolset ; 
 int /*<<< orphan*/  fts5IterSetOutputs_None ; 
 int /*<<< orphan*/  fts5IterSetOutputs_ZeroColset ; 
 int /*<<< orphan*/  sqlite3Fts5BufferSize (int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void fts5IterSetOutputCb(int *pRc, Fts5Iter *pIter){
  if( *pRc==SQLITE_OK ){
    Fts5Config *pConfig = pIter->pIndex->pConfig;
    if( pConfig->eDetail==FTS5_DETAIL_NONE ){
      pIter->xSetOutputs = fts5IterSetOutputs_None;
    }

    else if( pIter->pColset==0 ){
      pIter->xSetOutputs = fts5IterSetOutputs_Nocolset;
    }

    else if( pIter->pColset->nCol==0 ){
      pIter->xSetOutputs = fts5IterSetOutputs_ZeroColset;
    }

    else if( pConfig->eDetail==FTS5_DETAIL_FULL ){
      pIter->xSetOutputs = fts5IterSetOutputs_Full;
    }

    else{
      assert( pConfig->eDetail==FTS5_DETAIL_COLUMNS );
      if( pConfig->nCol<=100 ){
        pIter->xSetOutputs = fts5IterSetOutputs_Col100;
        sqlite3Fts5BufferSize(pRc, &pIter->poslist, pConfig->nCol);
      }else{
        pIter->xSetOutputs = fts5IterSetOutputs_Col;
      }
    }
  }
}