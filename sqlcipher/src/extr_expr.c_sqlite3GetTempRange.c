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
struct TYPE_4__ {int iRangeReg; int nRangeReg; int nMem; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 int sqlite3GetTempReg (TYPE_1__*) ; 

int sqlite3GetTempRange(Parse *pParse, int nReg){
  int i, n;
  if( nReg==1 ) return sqlite3GetTempReg(pParse);
  i = pParse->iRangeReg;
  n = pParse->nRangeReg;
  if( nReg<=n ){
    pParse->iRangeReg += nReg;
    pParse->nRangeReg -= nReg;
  }else{
    i = pParse->nMem+1;
    pParse->nMem += nReg;
  }
  return i;
}