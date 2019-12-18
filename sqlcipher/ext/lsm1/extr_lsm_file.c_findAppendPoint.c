#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* pDb; } ;
struct TYPE_12__ {int nRight; TYPE_1__* aRhs; } ;
struct TYPE_11__ {TYPE_2__* pWorker; } ;
struct TYPE_10__ {scalar_t__* aiAppend; } ;
struct TYPE_9__ {scalar_t__ iLastPg; } ;
typedef  scalar_t__ LsmPgno ;
typedef  TYPE_4__ Level ;
typedef  TYPE_5__ FileSystem ;

/* Variables and functions */
 int LSM_APPLIST_SZ ; 
 int fsPageToBlock (TYPE_5__*,scalar_t__) ; 

__attribute__((used)) static LsmPgno findAppendPoint(FileSystem *pFS, Level *pLvl){
  int i;
  LsmPgno *aiAppend = pFS->pDb->pWorker->aiAppend;
  LsmPgno iRet = 0;

  for(i=LSM_APPLIST_SZ-1; iRet==0 && i>=0; i--){
    if( (iRet = aiAppend[i]) ){
      if( pLvl ){
        int iBlk = fsPageToBlock(pFS, iRet);
        int j;
        for(j=0; iRet && j<pLvl->nRight; j++){
          if( fsPageToBlock(pFS, pLvl->aRhs[j].iLastPg)==iBlk ){
            iRet = 0;
          }
        }
      }
      if( iRet ) aiAppend[i] = 0;
    }
  }
  return iRet;
}