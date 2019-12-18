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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  lsm_db ;
struct TYPE_5__ {size_t iV2Child; int /*<<< orphan*/  iV2Ptr; int /*<<< orphan*/ * aiChildPtr; scalar_t__ iV2; int /*<<< orphan*/ * aiKeyPtr; } ;
typedef  TYPE_1__ TreeNode ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* newTreeNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static TreeNode *copyTreeNode(
  lsm_db *pDb, 
  TreeNode *pOld, 
  u32 *piNew, 
  int *pRc
){
  TreeNode *pNew;

  pNew = newTreeNode(pDb, piNew, pRc);
  if( pNew ){
    memcpy(pNew->aiKeyPtr, pOld->aiKeyPtr, sizeof(pNew->aiKeyPtr));
    memcpy(pNew->aiChildPtr, pOld->aiChildPtr, sizeof(pNew->aiChildPtr));
    if( pOld->iV2 ) pNew->aiChildPtr[pOld->iV2Child] = pOld->iV2Ptr;
  }
  return pNew;
}