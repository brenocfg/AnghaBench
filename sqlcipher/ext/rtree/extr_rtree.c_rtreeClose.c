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
struct TYPE_9__ {scalar_t__ pVtab; } ;
typedef  TYPE_1__ sqlite3_vtab_cursor ;
struct TYPE_11__ {scalar_t__ nCursor; } ;
struct TYPE_10__ {int /*<<< orphan*/ * aNode; struct TYPE_10__* aPoint; int /*<<< orphan*/  pReadAux; } ;
typedef  TYPE_2__ RtreeCursor ;
typedef  TYPE_3__ Rtree ;

/* Variables and functions */
 int RTREE_CACHE_SZ ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  freeCursorConstraints (TYPE_2__*) ; 
 int /*<<< orphan*/  nodeBlobReset (TYPE_3__*) ; 
 int /*<<< orphan*/  nodeRelease (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static int rtreeClose(sqlite3_vtab_cursor *cur){
  Rtree *pRtree = (Rtree *)(cur->pVtab);
  int ii;
  RtreeCursor *pCsr = (RtreeCursor *)cur;
  assert( pRtree->nCursor>0 );
  freeCursorConstraints(pCsr);
  sqlite3_finalize(pCsr->pReadAux);
  sqlite3_free(pCsr->aPoint);
  for(ii=0; ii<RTREE_CACHE_SZ; ii++) nodeRelease(pRtree, pCsr->aNode[ii]);
  sqlite3_free(pCsr);
  pRtree->nCursor--;
  nodeBlobReset(pRtree);
  return SQLITE_OK;
}