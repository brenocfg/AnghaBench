#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pAux; scalar_t__ xDelete; void* pPtr; struct TYPE_4__* pNext; } ;
struct TYPE_3__ {scalar_t__ pAux; TYPE_2__* pAuxdata; } ;
typedef  TYPE_1__ Fts5Cursor ;
typedef  int /*<<< orphan*/  Fts5Context ;
typedef  TYPE_2__ Fts5Auxdata ;

/* Variables and functions */

__attribute__((used)) static void *fts5ApiGetAuxdata(Fts5Context *pCtx, int bClear){
  Fts5Cursor *pCsr = (Fts5Cursor*)pCtx;
  Fts5Auxdata *pData;
  void *pRet = 0;

  for(pData=pCsr->pAuxdata; pData; pData=pData->pNext){
    if( pData->pAux==pCsr->pAux ) break;
  }

  if( pData ){
    pRet = pData->pPtr;
    if( bClear ){
      pData->pPtr = 0;
      pData->xDelete = 0;
    }
  }

  return pRet;
}