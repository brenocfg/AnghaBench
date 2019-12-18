#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int nCell; int iCell; int nKey; int nVal; int /*<<< orphan*/  pVal; int /*<<< orphan*/  blob2; int /*<<< orphan*/  eType; int /*<<< orphan*/  blob1; int /*<<< orphan*/  pKey; int /*<<< orphan*/  iPgPtr; scalar_t__ pPg; } ;
typedef  TYPE_1__ SegmentPtr ;

/* Variables and functions */
 scalar_t__ GETVARINT32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ GETVARINT64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int LSM_OK ; 
 size_t SEGMENT_CELLPTR_OFFSET (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fsPageData (scalar_t__,int*) ; 
 int lsmGetU16 (int /*<<< orphan*/ *) ; 
 scalar_t__ rtIsWrite (int /*<<< orphan*/ ) ; 
 int segmentPtrReadData (TYPE_1__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int segmentPtrLoadCell(
  SegmentPtr *pPtr,              /* Load page into this SegmentPtr object */
  int iNew                       /* Cell number of new cell */
){
  int rc = LSM_OK;
  if( pPtr->pPg ){
    u8 *aData;                    /* Pointer to page data buffer */
    int iOff;                     /* Offset in aData[] to read from */
    int nPgsz;                    /* Size of page (aData[]) in bytes */

    assert( iNew<pPtr->nCell );
    pPtr->iCell = iNew;
    aData = fsPageData(pPtr->pPg, &nPgsz);
    iOff = lsmGetU16(&aData[SEGMENT_CELLPTR_OFFSET(nPgsz, pPtr->iCell)]);
    pPtr->eType = aData[iOff];
    iOff++;
    iOff += GETVARINT64(&aData[iOff], pPtr->iPgPtr);
    iOff += GETVARINT32(&aData[iOff], pPtr->nKey);
    if( rtIsWrite(pPtr->eType) ){
      iOff += GETVARINT32(&aData[iOff], pPtr->nVal);
    }
    assert( pPtr->nKey>=0 );

    rc = segmentPtrReadData(
        pPtr, iOff, pPtr->nKey, &pPtr->pKey, &pPtr->blob1
    );
    if( rc==LSM_OK && rtIsWrite(pPtr->eType) ){
      rc = segmentPtrReadData(
          pPtr, iOff+pPtr->nKey, pPtr->nVal, &pPtr->pVal, &pPtr->blob2
      );
    }else{
      pPtr->nVal = 0;
      pPtr->pVal = 0;
    }
  }

  return rc;
}