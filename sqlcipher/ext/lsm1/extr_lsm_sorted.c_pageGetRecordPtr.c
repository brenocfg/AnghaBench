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
typedef  int /*<<< orphan*/  LsmPgno ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsmVarintGet64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pageGetCell (int /*<<< orphan*/ *,int,int) ; 
 int pageGetNRec (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static LsmPgno pageGetRecordPtr(u8 *aData, int nData, int iCell){
  LsmPgno iRet;                   /* Return value */
  u8 *aCell;                      /* Pointer to cell iCell */

  assert( iCell<pageGetNRec(aData, nData) && iCell>=0 );
  aCell = pageGetCell(aData, nData, iCell);
  lsmVarintGet64(&aCell[1], &iRet);
  return iRet;
}