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
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_5__ {int /*<<< orphan*/  pReadAux; scalar_t__ bAuxValid; } ;
typedef  TYPE_1__ RtreeCursor ;

/* Variables and functions */
 int /*<<< orphan*/  RTREE_QUEUE_TRACE (TYPE_1__*,char*) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  rtreeSearchPointPop (TYPE_1__*) ; 
 int rtreeStepToLeaf (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtreeNext(sqlite3_vtab_cursor *pVtabCursor){
  RtreeCursor *pCsr = (RtreeCursor *)pVtabCursor;
  int rc = SQLITE_OK;

  /* Move to the next entry that matches the configured constraints. */
  RTREE_QUEUE_TRACE(pCsr, "POP-Nx:");
  if( pCsr->bAuxValid ){
    pCsr->bAuxValid = 0;
    sqlite3_reset(pCsr->pReadAux);
  }
  rtreeSearchPointPop(pCsr);
  rc = rtreeStepToLeaf(pCsr);
  return rc;
}