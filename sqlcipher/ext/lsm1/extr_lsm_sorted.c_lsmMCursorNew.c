#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ iOldLog; } ;
struct TYPE_14__ {TYPE_7__* pClient; TYPE_1__ treehdr; TYPE_3__* pCsr; TYPE_3__* pCsrCache; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_16__ {scalar_t__ iLogOff; } ;
struct TYPE_15__ {int flags; scalar_t__* apTreeCsr; struct TYPE_15__* pNext; } ;
typedef  TYPE_3__ MultiCursor ;

/* Variables and functions */
 int CURSOR_IGNORE_DELETE ; 
 int CURSOR_IGNORE_SYSTEM ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsmMCursorClose (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmTreeCursorDestroy (scalar_t__) ; 
 int lsmTreeCursorNew (TYPE_2__*,int,scalar_t__*) ; 
 scalar_t__ lsmTreeHasOld (TYPE_2__*) ; 
 int multiCursorInit (TYPE_3__*,TYPE_7__*) ; 
 TYPE_3__* multiCursorNew (TYPE_2__*,int*) ; 

int lsmMCursorNew(
  lsm_db *pDb,                    /* Database handle */
  MultiCursor **ppCsr             /* OUT: Allocated cursor */
){
  MultiCursor *pCsr = 0;
  int rc = LSM_OK;

  if( pDb->pCsrCache ){
    int bOld;                     /* True if there is an old in-memory tree */

    /* Remove a cursor from the pCsrCache list and add it to the open list. */
    pCsr = pDb->pCsrCache;
    pDb->pCsrCache = pCsr->pNext;
    pCsr->pNext = pDb->pCsr;
    pDb->pCsr = pCsr;

    /* The cursor can almost be used as is, except that the old in-memory
    ** tree cursor may be present and not required, or required and not
    ** present. Fix this if required.  */
    bOld = (lsmTreeHasOld(pDb) && pDb->treehdr.iOldLog!=pDb->pClient->iLogOff);
    if( !bOld && pCsr->apTreeCsr[1] ){
      lsmTreeCursorDestroy(pCsr->apTreeCsr[1]);
      pCsr->apTreeCsr[1] = 0;
    }else if( bOld && !pCsr->apTreeCsr[1] ){
      rc = lsmTreeCursorNew(pDb, 1, &pCsr->apTreeCsr[1]);
    }

    pCsr->flags = (CURSOR_IGNORE_SYSTEM | CURSOR_IGNORE_DELETE);

  }else{
    pCsr = multiCursorNew(pDb, &rc);
    if( rc==LSM_OK ) rc = multiCursorInit(pCsr, pDb->pClient);
  }

  if( rc!=LSM_OK ){
    lsmMCursorClose(pCsr, 0);
    pCsr = 0;
  }
  assert( (rc==LSM_OK)==(pCsr!=0) );
  *ppCsr = pCsr;
  return rc;
}