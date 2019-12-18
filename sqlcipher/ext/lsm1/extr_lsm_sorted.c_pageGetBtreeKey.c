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
struct TYPE_4__ {int nData; void* pData; } ;
typedef  int /*<<< orphan*/  Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  LsmPgno ;
typedef  TYPE_1__ LsmBlob ;

/* Variables and functions */
 int /*<<< orphan*/  GETVARINT32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GETVARINT64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int LSM_OK ; 
 int SEGMENT_BTREE_FLAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fsPageData (int /*<<< orphan*/ *,int*) ; 
 int lsmFsDbPageGet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lsmFsPageRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmPageEnv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmPageFS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pageGetCell (int /*<<< orphan*/ *,int,int) ; 
 int pageGetFlags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pageGetKeyCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,TYPE_1__*) ; 
 int pageGetNRec (int /*<<< orphan*/ *,int) ; 
 int rtTopic (int) ; 

__attribute__((used)) static int pageGetBtreeKey(
  Segment *pSeg,                  /* Segment page pPg belongs to */
  Page *pPg,
  int iKey, 
  LsmPgno *piPtr, 
  int *piTopic, 
  void **ppKey,
  int *pnKey,
  LsmBlob *pBlob
){
  u8 *aData;
  int nData;
  u8 *aCell;
  int eType;

  aData = fsPageData(pPg, &nData);
  assert( SEGMENT_BTREE_FLAG & pageGetFlags(aData, nData) );
  assert( iKey>=0 && iKey<pageGetNRec(aData, nData) );

  aCell = pageGetCell(aData, nData, iKey);
  eType = *aCell++;
  aCell += GETVARINT64(aCell, *piPtr);

  if( eType==0 ){
    int rc;
    LsmPgno iRef;               /* Page number of referenced page */
    Page *pRef;
    aCell += GETVARINT64(aCell, iRef);
    rc = lsmFsDbPageGet(lsmPageFS(pPg), pSeg, iRef, &pRef);
    if( rc!=LSM_OK ) return rc;
    pageGetKeyCopy(lsmPageEnv(pPg), pSeg, pRef, 0, &eType, pBlob);
    lsmFsPageRelease(pRef);
    *ppKey = pBlob->pData;
    *pnKey = pBlob->nData;
  }else{
    aCell += GETVARINT32(aCell, *pnKey);
    *ppKey = aCell;
  }
  if( piTopic ) *piTopic = rtTopic(eType);

  return LSM_OK;
}