#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_int64 ;
struct TYPE_6__ {int nCol; } ;
typedef  TYPE_1__ Fts5Colset ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,size_t) ; 
 scalar_t__ sqlite3Fts5MallocZero (int*,int) ; 

__attribute__((used)) static Fts5Colset *fts5CloneColset(int *pRc, Fts5Colset *pOrig){
  Fts5Colset *pRet;
  if( pOrig ){
    sqlite3_int64 nByte = sizeof(Fts5Colset) + (pOrig->nCol-1) * sizeof(int);
    pRet = (Fts5Colset*)sqlite3Fts5MallocZero(pRc, nByte);
    if( pRet ){ 
      memcpy(pRet, pOrig, (size_t)nByte);
    }
  }else{
    pRet = 0;
  }
  return pRet;
}