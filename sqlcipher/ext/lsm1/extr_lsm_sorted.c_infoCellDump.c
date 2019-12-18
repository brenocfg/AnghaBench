#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int /*<<< orphan*/  pEnv; int /*<<< orphan*/  pFS; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_8__ {int nData; scalar_t__ pData; } ;
typedef  int /*<<< orphan*/  Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  LsmPgno ;
typedef  TYPE_2__ LsmBlob ;

/* Variables and functions */
 int /*<<< orphan*/ * fsPageData (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  lsmFsDbPageGet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lsmFsPageRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmVarintGet32 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  lsmVarintGet64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pageGetCell (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pageGetKeyCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,TYPE_2__*) ; 
 scalar_t__ rtIsWrite (int) ; 
 int /*<<< orphan*/  sortedReadData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,void**,TYPE_2__*) ; 

__attribute__((used)) static void infoCellDump(
  lsm_db *pDb,                    /* Database handle */
  Segment *pSeg,                  /* Segment page belongs to */
  int bIndirect,                  /* True to follow indirect refs */
  Page *pPg,
  int iCell,
  int *peType,
  int *piPgPtr,
  u8 **paKey, int *pnKey,
  u8 **paVal, int *pnVal,
  LsmBlob *pBlob
){
  u8 *aData; int nData;           /* Page data */
  u8 *aKey; int nKey = 0;         /* Key */
  u8 *aVal = 0; int nVal = 0;     /* Value */
  int eType;
  int iPgPtr;
  Page *pRef = 0;                 /* Pointer to page iRef */
  u8 *aCell;

  aData = fsPageData(pPg, &nData);

  aCell = pageGetCell(aData, nData, iCell);
  eType = *aCell++;
  aCell += lsmVarintGet32(aCell, &iPgPtr);

  if( eType==0 ){
    int dummy;
    LsmPgno iRef;                 /* Page number of referenced page */
    aCell += lsmVarintGet64(aCell, &iRef);
    if( bIndirect ){
      lsmFsDbPageGet(pDb->pFS, pSeg, iRef, &pRef);
      pageGetKeyCopy(pDb->pEnv, pSeg, pRef, 0, &dummy, pBlob);
      aKey = (u8 *)pBlob->pData;
      nKey = pBlob->nData;
      lsmFsPageRelease(pRef);
    }else{
      aKey = (u8 *)"<indirect>";
      nKey = 11;
    }
  }else{
    aCell += lsmVarintGet32(aCell, &nKey);
    if( rtIsWrite(eType) ) aCell += lsmVarintGet32(aCell, &nVal);
    sortedReadData(pSeg, pPg, (aCell-aData), nKey+nVal, (void **)&aKey, pBlob);
    aVal = &aKey[nKey];
  }

  if( peType ) *peType = eType;
  if( piPgPtr ) *piPgPtr = iPgPtr;
  if( paKey ) *paKey = aKey;
  if( paVal ) *paVal = aVal;
  if( pnKey ) *pnKey = nKey;
  if( pnVal ) *pnVal = nVal;
}