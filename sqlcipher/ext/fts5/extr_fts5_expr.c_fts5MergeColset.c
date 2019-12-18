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
struct TYPE_4__ {int nCol; int* aiCol; } ;
typedef  TYPE_1__ Fts5Colset ;

/* Variables and functions */

__attribute__((used)) static void fts5MergeColset(Fts5Colset *pColset, Fts5Colset *pMerge){
  int iIn = 0;          /* Next input in pColset */
  int iMerge = 0;       /* Next input in pMerge */
  int iOut = 0;         /* Next output slot in pColset */

  while( iIn<pColset->nCol && iMerge<pMerge->nCol ){
    int iDiff = pColset->aiCol[iIn] - pMerge->aiCol[iMerge];
    if( iDiff==0 ){
      pColset->aiCol[iOut++] = pMerge->aiCol[iMerge];
      iMerge++;
      iIn++;
    }else if( iDiff>0 ){
      iMerge++;
    }else{
      iIn++;
    }
  }
  pColset->nCol = iOut;
}