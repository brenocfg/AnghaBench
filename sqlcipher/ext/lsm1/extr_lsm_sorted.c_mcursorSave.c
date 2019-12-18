#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* aTree; } ;
typedef  TYPE_1__ MultiCursor ;

/* Variables and functions */
 int CURSOR_DATA_TREE0 ; 
 int CURSOR_DATA_TREE1 ; 
 int LSM_OK ; 
 int /*<<< orphan*/  mcursorFreeComponents (TYPE_1__*) ; 
 int /*<<< orphan*/  multiCursorCacheKey (TYPE_1__*,int*) ; 

int mcursorSave(MultiCursor *pCsr){
  int rc = LSM_OK;
  if( pCsr->aTree ){
    int iTree = pCsr->aTree[1];
    if( iTree==CURSOR_DATA_TREE0 || iTree==CURSOR_DATA_TREE1 ){
      multiCursorCacheKey(pCsr, &rc);
    }
  }
  mcursorFreeComponents(pCsr);
  return rc;
}