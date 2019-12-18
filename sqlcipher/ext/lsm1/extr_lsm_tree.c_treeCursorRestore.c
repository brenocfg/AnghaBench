#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nKey; } ;
typedef  TYPE_1__ TreeKey ;
struct TYPE_7__ {TYPE_1__* pSave; } ;
typedef  TYPE_2__ TreeCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  TKV_KEY (TYPE_1__*) ; 
 int lsmTreeCursorSeek (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int treeCursorRestore(TreeCursor *pCsr, int *pRes){
  int rc = LSM_OK;
  if( pCsr->pSave ){
    TreeKey *pKey = pCsr->pSave;
    pCsr->pSave = 0;
    if( pRes ){
      rc = lsmTreeCursorSeek(pCsr, TKV_KEY(pKey), pKey->nKey, pRes);
    }
  }
  return rc;
}