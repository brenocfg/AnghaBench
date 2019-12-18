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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ LsmPgno ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__* fsPageData (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  lsmVarintGet64 (scalar_t__*,scalar_t__*) ; 
 scalar_t__* pageGetCell (scalar_t__*,int,int) ; 

__attribute__((used)) static LsmPgno pageGetBtreeRef(Page *pPg, int iKey){
  LsmPgno iRef;
  u8 *aData;
  int nData;
  u8 *aCell;

  aData = fsPageData(pPg, &nData);
  aCell = pageGetCell(aData, nData, iKey);
  assert( aCell[0]==0 );
  aCell++;
  aCell += lsmVarintGet64(aCell, &iRef);
  lsmVarintGet64(aCell, &iRef);
  assert( iRef>0 );
  return iRef;
}