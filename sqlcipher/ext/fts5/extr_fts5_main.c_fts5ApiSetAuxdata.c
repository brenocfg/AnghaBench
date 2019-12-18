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
struct TYPE_4__ {scalar_t__ pAux; void (* xDelete ) (void*) ;void* pPtr; struct TYPE_4__* pNext; } ;
struct TYPE_3__ {scalar_t__ pAux; TYPE_2__* pAuxdata; } ;
typedef  TYPE_1__ Fts5Cursor ;
typedef  int /*<<< orphan*/  Fts5Context ;
typedef  TYPE_2__ Fts5Auxdata ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ sqlite3Fts5MallocZero (int*,int) ; 
 void stub1 (void*) ; 

__attribute__((used)) static int fts5ApiSetAuxdata(
  Fts5Context *pCtx,              /* Fts5 context */
  void *pPtr,                     /* Pointer to save as auxdata */
  void(*xDelete)(void*)           /* Destructor for pPtr (or NULL) */
){
  Fts5Cursor *pCsr = (Fts5Cursor*)pCtx;
  Fts5Auxdata *pData;

  /* Search through the cursors list of Fts5Auxdata objects for one that
  ** corresponds to the currently executing auxiliary function.  */
  for(pData=pCsr->pAuxdata; pData; pData=pData->pNext){
    if( pData->pAux==pCsr->pAux ) break;
  }

  if( pData ){
    if( pData->xDelete ){
      pData->xDelete(pData->pPtr);
    }
  }else{
    int rc = SQLITE_OK;
    pData = (Fts5Auxdata*)sqlite3Fts5MallocZero(&rc, sizeof(Fts5Auxdata));
    if( pData==0 ){
      if( xDelete ) xDelete(pPtr);
      return rc;
    }
    pData->pAux = pCsr->pAux;
    pData->pNext = pCsr->pAuxdata;
    pCsr->pAuxdata = pData;
  }

  pData->xDelete = xDelete;
  pData->pPtr = pPtr;
  return SQLITE_OK;
}