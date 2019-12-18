#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TreeCursor ;
struct TYPE_5__ {int nData; void* pData; } ;
struct TYPE_6__ {int flags; int* aTree; int eType; TYPE_1__ key; int /*<<< orphan*/ ** apTreeCsr; } ;
typedef  TYPE_2__ MultiCursor ;

/* Variables and functions */
 int CURSOR_DATA_TREE0 ; 
 int CURSOR_DATA_TREE1 ; 
 int CURSOR_SEEK_EQ ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsmTreeCursorKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int*) ; 
 scalar_t__ memcmp (void*,void*,int) ; 
 int /*<<< orphan*/  multiCursorGetKey (TYPE_2__*,int,int*,void**,int*) ; 

int lsmMCursorKey(MultiCursor *pCsr, void **ppKey, int *pnKey){
  if( (pCsr->flags & CURSOR_SEEK_EQ) || pCsr->aTree==0 ){
    *pnKey = pCsr->key.nData;
    *ppKey = pCsr->key.pData;
  }else{
    int iKey = pCsr->aTree[1];

    if( iKey==CURSOR_DATA_TREE0 || iKey==CURSOR_DATA_TREE1 ){
      TreeCursor *pTreeCsr = pCsr->apTreeCsr[iKey-CURSOR_DATA_TREE0];
      lsmTreeCursorKey(pTreeCsr, 0, ppKey, pnKey);
    }else{
      int nKey;

#ifndef NDEBUG
      void *pKey;
      int eType;
      multiCursorGetKey(pCsr, iKey, &eType, &pKey, &nKey);
      assert( eType==pCsr->eType );
      assert( nKey==pCsr->key.nData );
      assert( memcmp(pKey, pCsr->key.pData, nKey)==0 );
#endif

      nKey = pCsr->key.nData;
      if( nKey==0 ){
        *ppKey = 0;
      }else{
        *ppKey = pCsr->key.pData;
      }
      *pnKey = nKey; 
    }
  }
  return LSM_OK;
}