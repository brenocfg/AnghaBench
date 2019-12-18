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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  LsmBlob ;

/* Variables and functions */
 int SEGMENT_BTREE_FLAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fsPageData (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  lsmVarintGet32 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * pageGetCell (int /*<<< orphan*/ *,int,int) ; 
 int pageGetFlags (int /*<<< orphan*/ *,int) ; 
 int pageGetNRec (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rtIsWrite (int) ; 
 int rtTopic (int) ; 
 int /*<<< orphan*/  sortedReadData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 *pageGetKey(
  Segment *pSeg,                  /* Segment pPg belongs to */
  Page *pPg,                      /* Page to read from */
  int iCell,                      /* Index of cell on page to read */
  int *piTopic,                   /* OUT: Topic associated with this key */
  int *pnKey,                     /* OUT: Size of key in bytes */
  LsmBlob *pBlob                  /* If required, use this for dynamic memory */
){
  u8 *pKey;
  int nDummy;
  int eType;
  u8 *aData;
  int nData;

  aData = fsPageData(pPg, &nData);

  assert( !(pageGetFlags(aData, nData) & SEGMENT_BTREE_FLAG) );
  assert( iCell<pageGetNRec(aData, nData) );

  pKey = pageGetCell(aData, nData, iCell);
  eType = *pKey++;
  pKey += lsmVarintGet32(pKey, &nDummy);
  pKey += lsmVarintGet32(pKey, pnKey);
  if( rtIsWrite(eType) ){
    pKey += lsmVarintGet32(pKey, &nDummy);
  }
  *piTopic = rtTopic(eType);

  sortedReadData(pSeg, pPg, pKey-aData, *pnKey, (void **)&pKey, pBlob);
  return pKey;
}