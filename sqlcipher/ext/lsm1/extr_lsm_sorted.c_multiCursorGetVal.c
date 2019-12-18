#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  TreeCursor ;
struct TYPE_13__ {int iFree; int nPtr; TYPE_5__* aPtr; scalar_t__ pSystemVal; TYPE_1__* pDb; int /*<<< orphan*/ ** apTreeCsr; } ;
struct TYPE_12__ {int nVal; void* pVal; int /*<<< orphan*/  pPg; } ;
struct TYPE_10__ {int nEntry; TYPE_2__* aEntry; } ;
struct TYPE_11__ {TYPE_3__ freelist; } ;
struct TYPE_9__ {int /*<<< orphan*/  iId; } ;
struct TYPE_8__ {TYPE_4__* pWorker; } ;
typedef  TYPE_4__ Snapshot ;
typedef  TYPE_5__ SegmentPtr ;
typedef  TYPE_6__ MultiCursor ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_DATA_SEGMENT ; 
#define  CURSOR_DATA_SYSTEM 130 
#define  CURSOR_DATA_TREE0 129 
#define  CURSOR_DATA_TREE1 128 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsmPutU64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmTreeCursorValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmTreeCursorValue (int /*<<< orphan*/ *,void**,int*) ; 

__attribute__((used)) static int multiCursorGetVal(
  MultiCursor *pCsr, 
  int iVal, 
  void **ppVal, 
  int *pnVal
){
  int rc = LSM_OK;

  *ppVal = 0;
  *pnVal = 0;

  switch( iVal ){
    case CURSOR_DATA_TREE0:
    case CURSOR_DATA_TREE1: {
      TreeCursor *pTreeCsr = pCsr->apTreeCsr[iVal-CURSOR_DATA_TREE0];
      if( lsmTreeCursorValid(pTreeCsr) ){
        lsmTreeCursorValue(pTreeCsr, ppVal, pnVal);
      }else{
        *ppVal = 0;
        *pnVal = 0;
      }
      break;
    }

    case CURSOR_DATA_SYSTEM: {
      Snapshot *pWorker = pCsr->pDb->pWorker;
      if( pWorker 
       && (pCsr->iFree % 2)==0
       && pCsr->iFree < (pWorker->freelist.nEntry*2)
      ){
        int iEntry = pWorker->freelist.nEntry - 1 - (pCsr->iFree / 2);
        u8 *aVal = &((u8 *)(pCsr->pSystemVal))[4];
        lsmPutU64(aVal, pWorker->freelist.aEntry[iEntry].iId);
        *ppVal = aVal;
        *pnVal = 8;
      }
      break;
    }

    default: {
      int iPtr = iVal-CURSOR_DATA_SEGMENT;
      if( iPtr<pCsr->nPtr ){
        SegmentPtr *pPtr = &pCsr->aPtr[iPtr];
        if( pPtr->pPg ){
          *ppVal = pPtr->pVal;
          *pnVal = pPtr->nVal;
        }
      }
    }
  }

  assert( rc==LSM_OK || (*ppVal==0 && *pnVal==0) );
  return rc;
}