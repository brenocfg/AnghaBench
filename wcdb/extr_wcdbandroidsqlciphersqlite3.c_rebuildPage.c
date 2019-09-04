#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uptr ;
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct TYPE_10__ {int* ixNx; int* szCell; int /*<<< orphan*/ ** apEnd; int /*<<< orphan*/ ** apCell; } ;
struct TYPE_9__ {int hdrOffset; int (* xCellSize ) (TYPE_2__*,int /*<<< orphan*/ *) ;int nCell; scalar_t__ nOverflow; TYPE_1__* pBt; int /*<<< orphan*/ * aCellIdx; int /*<<< orphan*/ * aData; } ;
struct TYPE_8__ {int usableSize; int /*<<< orphan*/  pPager; } ;
typedef  TYPE_2__ MemPage ;
typedef  TYPE_3__ CellArray ;

/* Variables and functions */
 scalar_t__ ALWAYS (int) ; 
 scalar_t__ CORRUPT_DB ; 
 int NB ; 
 scalar_t__ NEVER (int) ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_WITHIN (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t get2byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  put2byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sqlite3PagerTempSpace (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int rebuildPage(
  CellArray *pCArray,             /* Content to be added to page pPg */
  int iFirst,                     /* First cell in pCArray to use */
  int nCell,                      /* Final number of cells on page */
  MemPage *pPg                    /* The page to be reconstructed */
){
  const int hdr = pPg->hdrOffset;          /* Offset of header on pPg */
  u8 * const aData = pPg->aData;           /* Pointer to data for pPg */
  const int usableSize = pPg->pBt->usableSize;
  u8 * const pEnd = &aData[usableSize];
  int i = iFirst;                 /* Which cell to copy from pCArray*/
  u32 j;                          /* Start of cell content area */
  int iEnd = i+nCell;             /* Loop terminator */
  u8 *pCellptr = pPg->aCellIdx;
  u8 *pTmp = sqlite3PagerTempSpace(pPg->pBt->pPager);
  u8 *pData;
  int k;                          /* Current slot in pCArray->apEnd[] */
  u8 *pSrcEnd;                    /* Current pCArray->apEnd[k] value */

  assert( i<iEnd );
  j = get2byte(&aData[hdr+5]);
  if( NEVER(j>(u32)usableSize) ){ j = 0; }
  memcpy(&pTmp[j], &aData[j], usableSize - j);

  for(k=0; pCArray->ixNx[k]<=i && ALWAYS(k<NB*2); k++){}
  pSrcEnd = pCArray->apEnd[k];

  pData = pEnd;
  while( 1/*exit by break*/ ){
    u8 *pCell = pCArray->apCell[i];
    u16 sz = pCArray->szCell[i];
    assert( sz>0 );
    if( SQLITE_WITHIN(pCell,aData,pEnd) ){
      if( ((uptr)(pCell+sz))>(uptr)pEnd ) return SQLITE_CORRUPT_BKPT;
      pCell = &pTmp[pCell - aData];
    }else if( (uptr)(pCell+sz)>(uptr)pSrcEnd
           && (uptr)(pCell)<(uptr)pSrcEnd
    ){
      return SQLITE_CORRUPT_BKPT;
    }

    pData -= sz;
    put2byte(pCellptr, (pData - aData));
    pCellptr += 2;
    if( pData < pCellptr ) return SQLITE_CORRUPT_BKPT;
    memcpy(pData, pCell, sz);
    assert( sz==pPg->xCellSize(pPg, pCell) || CORRUPT_DB );
    testcase( sz!=pPg->xCellSize(pPg,pCell) );
    i++;
    if( i>=iEnd ) break;
    if( pCArray->ixNx[k]<=i ){
      k++;
      pSrcEnd = pCArray->apEnd[k];
    }
  }

  /* The pPg->nFree field is now set incorrectly. The caller will fix it. */
  pPg->nCell = nCell;
  pPg->nOverflow = 0;

  put2byte(&aData[hdr+1], 0);
  put2byte(&aData[hdr+3], pPg->nCell);
  put2byte(&aData[hdr+5], pData - aData);
  aData[hdr+7] = 0x00;
  return SQLITE_OK;
}