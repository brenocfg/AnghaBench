#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* pDb; } ;
struct TYPE_14__ {TYPE_11__* pSeg; } ;
struct TYPE_13__ {int /*<<< orphan*/  pFS; } ;
struct TYPE_12__ {scalar_t__ iRoot; scalar_t__ iFirst; } ;
typedef  TYPE_2__ SegmentPtr ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_3__ MultiCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int seekInBtree (TYPE_3__*,TYPE_11__*,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int segmentPtrLoadPage (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int segmentPtrSeek (TYPE_3__*,TYPE_2__*,int,void*,int,int,int*,int*) ; 
 int /*<<< orphan*/  segmentPtrSetPage (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int seekInSegment(
  MultiCursor *pCsr, 
  SegmentPtr *pPtr,
  int iTopic,
  void *pKey, int nKey,
  int iPg,                        /* Page to search */
  int eSeek,                      /* Search bias - see above */
  int *piPtr,                     /* OUT: FC pointer */
  int *pbStop                     /* OUT: Stop search flag */
){
  int iPtr = iPg;
  int rc = LSM_OK;

  if( pPtr->pSeg->iRoot ){
    Page *pPg;
    assert( pPtr->pSeg->iRoot!=0 );
    rc = seekInBtree(pCsr, pPtr->pSeg, iTopic, pKey, nKey, 0, &pPg);
    if( rc==LSM_OK ) segmentPtrSetPage(pPtr, pPg);
  }else{
    if( iPtr==0 ){
      iPtr = (int)pPtr->pSeg->iFirst;
    }
    if( rc==LSM_OK ){
      rc = segmentPtrLoadPage(pCsr->pDb->pFS, pPtr, iPtr);
    }
  }

  if( rc==LSM_OK ){
    rc = segmentPtrSeek(pCsr, pPtr, iTopic, pKey, nKey, eSeek, piPtr, pbStop);
  }
  return rc;
}