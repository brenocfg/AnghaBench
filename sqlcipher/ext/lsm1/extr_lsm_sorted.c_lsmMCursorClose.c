#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pEnv; TYPE_3__* pCsrCache; TYPE_3__* pCsr; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_9__ {int nPtr; int /*<<< orphan*/  val; int /*<<< orphan*/  key; struct TYPE_9__* pNext; int /*<<< orphan*/ * apTreeCsr; TYPE_2__* aPtr; int /*<<< orphan*/  pBtCsr; TYPE_1__* pDb; } ;
struct TYPE_8__ {scalar_t__ pPg; } ;
typedef  TYPE_2__ SegmentPtr ;
typedef  TYPE_3__ MultiCursor ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  lsmFsPageRelease (scalar_t__) ; 
 int /*<<< orphan*/  lsmTreeCursorReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcursorFreeComponents (TYPE_3__*) ; 
 int /*<<< orphan*/  sortedBlobFree (int /*<<< orphan*/ *) ; 

void lsmMCursorClose(MultiCursor *pCsr, int bCache){
  if( pCsr ){
    lsm_db *pDb = pCsr->pDb;
    MultiCursor **pp;             /* Iterator variable */

    /* The cursor may or may not be currently part of the linked list 
    ** starting at lsm_db.pCsr. If it is, extract it.  */
    for(pp=&pDb->pCsr; *pp; pp=&((*pp)->pNext)){
      if( *pp==pCsr ){
        *pp = pCsr->pNext;
        break;
      }
    }

    if( bCache ){
      int i;                      /* Used to iterate through segment-pointers */

      /* Release any page references held by this cursor. */
      assert( !pCsr->pBtCsr );
      for(i=0; i<pCsr->nPtr; i++){
        SegmentPtr *pPtr = &pCsr->aPtr[i];
        lsmFsPageRelease(pPtr->pPg);
        pPtr->pPg = 0;
      }

      /* Reset the tree cursors */
      lsmTreeCursorReset(pCsr->apTreeCsr[0]);
      lsmTreeCursorReset(pCsr->apTreeCsr[1]);

      /* Add the cursor to the pCsrCache list */
      pCsr->pNext = pDb->pCsrCache;
      pDb->pCsrCache = pCsr;
    }else{
      /* Free the allocation used to cache the current key, if any. */
      sortedBlobFree(&pCsr->key);
      sortedBlobFree(&pCsr->val);

      /* Free the component cursors */
      mcursorFreeComponents(pCsr);

      /* Free the cursor structure itself */
      lsmFree(pDb->pEnv, pCsr);
    }
  }
}