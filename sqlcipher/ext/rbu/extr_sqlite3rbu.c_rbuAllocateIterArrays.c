#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3rbu ;
typedef  int sqlite3_int64 ;
struct TYPE_3__ {char** azTblCol; char** azTblType; int* aiSrcOrder; int /*<<< orphan*/ * abNotNull; int /*<<< orphan*/ * abIndexed; int /*<<< orphan*/ * abTblPk; } ;
typedef  TYPE_1__ RbuObjIter ;

/* Variables and functions */
 scalar_t__ rbuMalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rbuAllocateIterArrays(sqlite3rbu *p, RbuObjIter *pIter, int nCol){
  sqlite3_int64 nByte = (2*sizeof(char*) + sizeof(int) + 3*sizeof(u8)) * nCol;
  char **azNew;

  azNew = (char**)rbuMalloc(p, nByte);
  if( azNew ){
    pIter->azTblCol = azNew;
    pIter->azTblType = &azNew[nCol];
    pIter->aiSrcOrder = (int*)&pIter->azTblType[nCol];
    pIter->abTblPk = (u8*)&pIter->aiSrcOrder[nCol];
    pIter->abNotNull = (u8*)&pIter->abTblPk[nCol];
    pIter->abIndexed = (u8*)&pIter->abNotNull[nCol];
  }
}