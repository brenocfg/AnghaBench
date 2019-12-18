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
struct TYPE_4__ {int iNode; int /*<<< orphan*/  blob; int /*<<< orphan*/  pSave; } ;
typedef  TYPE_1__ TreeCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  csrGetKey (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 

int lsmTreeCursorSave(TreeCursor *pCsr){
  int rc = LSM_OK;
  if( pCsr && pCsr->pSave==0 ){
    int iNode = pCsr->iNode;
    if( iNode>=0 ){
      pCsr->pSave = csrGetKey(pCsr, &pCsr->blob, &rc);
    }
    pCsr->iNode = -1;
  }
  return rc;
}