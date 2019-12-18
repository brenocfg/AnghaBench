#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nBusy; scalar_t__ nCursor; scalar_t__ nNodeRef; struct TYPE_5__* zReadAuxSql; int /*<<< orphan*/  pWriteAux; int /*<<< orphan*/  pDeleteParent; int /*<<< orphan*/  pWriteParent; int /*<<< orphan*/  pReadParent; int /*<<< orphan*/  pDeleteRowid; int /*<<< orphan*/  pWriteRowid; int /*<<< orphan*/  pReadRowid; int /*<<< orphan*/  pDeleteNode; int /*<<< orphan*/  pWriteNode; scalar_t__ bCorrupt; scalar_t__ inWrTrans; } ;
typedef  TYPE_1__ Rtree ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nodeBlobReset (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static void rtreeRelease(Rtree *pRtree){
  pRtree->nBusy--;
  if( pRtree->nBusy==0 ){
    pRtree->inWrTrans = 0;
    assert( pRtree->nCursor==0 );
    nodeBlobReset(pRtree);
    assert( pRtree->nNodeRef==0 || pRtree->bCorrupt );
    sqlite3_finalize(pRtree->pWriteNode);
    sqlite3_finalize(pRtree->pDeleteNode);
    sqlite3_finalize(pRtree->pReadRowid);
    sqlite3_finalize(pRtree->pWriteRowid);
    sqlite3_finalize(pRtree->pDeleteRowid);
    sqlite3_finalize(pRtree->pReadParent);
    sqlite3_finalize(pRtree->pWriteParent);
    sqlite3_finalize(pRtree->pDeleteParent);
    sqlite3_finalize(pRtree->pWriteAux);
    sqlite3_free(pRtree->zReadAuxSql);
    sqlite3_free(pRtree);
  }
}