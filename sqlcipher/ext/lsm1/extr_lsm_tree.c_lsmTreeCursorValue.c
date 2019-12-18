#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; int nValue; } ;
typedef  TYPE_1__ TreeKey ;
struct TYPE_9__ {int /*<<< orphan*/  blob; } ;
typedef  TYPE_2__ TreeCursor ;

/* Variables and functions */
 int LSM_INSERT ; 
 int LSM_OK ; 
 void* TKV_VAL (TYPE_1__*) ; 
 TYPE_1__* csrGetKey (TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int treeCursorRestore (TYPE_2__*,int*) ; 

int lsmTreeCursorValue(TreeCursor *pCsr, void **ppVal, int *pnVal){
  int res = 0;
  int rc;

  rc = treeCursorRestore(pCsr, &res);
  if( res==0 ){
    TreeKey *pTreeKey = csrGetKey(pCsr, &pCsr->blob, &rc);
    if( rc==LSM_OK ){
      if( pTreeKey->flags & LSM_INSERT ){
        *pnVal = pTreeKey->nValue;
        *ppVal = TKV_VAL(pTreeKey);
      }else{
        *ppVal = 0;
        *pnVal = -1;
      }
    }
  }else{
    *ppVal = 0;
    *pnVal = 0;
  }

  return rc;
}