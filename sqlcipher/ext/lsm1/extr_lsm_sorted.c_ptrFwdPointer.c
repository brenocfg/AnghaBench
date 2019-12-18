#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ LsmPgno ;

/* Variables and functions */
 int LSM_OK ; 
 int LSM_START_DELETE ; 
 int SEGMENT_BTREE_FLAG ; 
 int lsmFsDbPageNext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int* lsmFsPageData (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  lsmFsPageRelease (int /*<<< orphan*/ *) ; 
 int* pageGetCell (int*,int,int) ; 
 int pageGetFlags (int*,int) ; 
 int pageGetNRec (int*,int) ; 
 scalar_t__ pageGetPtr (int*,int) ; 
 scalar_t__ pageGetRecordPtr (int*,int,int) ; 

__attribute__((used)) static int ptrFwdPointer(
  Page *pPage,
  int iCell,
  Segment *pSeg,
  LsmPgno *piPtr,
  int *pbFound
){
  Page *pPg = pPage;
  int iFirst = iCell;
  int rc = LSM_OK;

  do {
    Page *pNext = 0;
    u8 *aData;
    int nData;

    aData = lsmFsPageData(pPg, &nData);
    if( (pageGetFlags(aData, nData) & SEGMENT_BTREE_FLAG)==0 ){
      int i;
      int nCell = pageGetNRec(aData, nData);
      for(i=iFirst; i<nCell; i++){
        u8 eType = *pageGetCell(aData, nData, i);
        if( (eType & LSM_START_DELETE)==0 ){
          *pbFound = 1;
          *piPtr = pageGetRecordPtr(aData, nData, i) + pageGetPtr(aData, nData);
          lsmFsPageRelease(pPg);
          return LSM_OK;
        }
      }
    }

    rc = lsmFsDbPageNext(pSeg, pPg, 1, &pNext);
    lsmFsPageRelease(pPg);
    pPg = pNext;
    iFirst = 0;
  }while( pPg && rc==LSM_OK );
  lsmFsPageRelease(pPg);

  *pbFound = 0;
  return rc;
}