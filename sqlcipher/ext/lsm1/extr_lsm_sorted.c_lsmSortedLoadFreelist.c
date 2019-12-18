#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int pWorker; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_11__ {int nData; int /*<<< orphan*/  pData; } ;
struct TYPE_13__ {TYPE_1__ key; int /*<<< orphan*/  eType; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ MultiCursor ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_IGNORE_DELETE ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsmMCursorClose (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int lsmMCursorLast (TYPE_3__*) ; 
 int lsmMCursorValue (TYPE_3__*,void**,int*) ; 
 void* lsmMallocRc (int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int multiCursorAddAll (TYPE_3__*,int) ; 
 TYPE_3__* multiCursorNew (TYPE_2__*,int*) ; 
 scalar_t__ rtIsSystem (int /*<<< orphan*/ ) ; 
 scalar_t__ rtIsWrite (int /*<<< orphan*/ ) ; 

int lsmSortedLoadFreelist(
  lsm_db *pDb,                    /* Database handle (must be worker) */
  void **ppVal,                   /* OUT: Blob containing LSM free-list */
  int *pnVal                      /* OUT: Size of *ppVal blob in bytes */
){
  MultiCursor *pCsr;              /* Cursor used to retreive free-list */
  int rc = LSM_OK;                /* Return Code */

  assert( pDb->pWorker );
  assert( *ppVal==0 && *pnVal==0 );

  pCsr = multiCursorNew(pDb, &rc);
  if( pCsr ){
    rc = multiCursorAddAll(pCsr, pDb->pWorker);
    pCsr->flags |= CURSOR_IGNORE_DELETE;
  }
  
  if( rc==LSM_OK ){
    rc = lsmMCursorLast(pCsr);
    if( rc==LSM_OK 
     && rtIsWrite(pCsr->eType) && rtIsSystem(pCsr->eType)
     && pCsr->key.nData==8 
     && 0==memcmp(pCsr->key.pData, "FREELIST", 8)
    ){
      void *pVal; int nVal;         /* Value read from database */
      rc = lsmMCursorValue(pCsr, &pVal, &nVal);
      if( rc==LSM_OK ){
        *ppVal = lsmMallocRc(pDb->pEnv, nVal, &rc);
        if( *ppVal ){
          memcpy(*ppVal, pVal, nVal);
          *pnVal = nVal;
        }
      }
    }

    lsmMCursorClose(pCsr, 0);
  }

  return rc;
}