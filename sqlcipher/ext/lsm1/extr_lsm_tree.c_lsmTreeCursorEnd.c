#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  lsm_db ;
struct TYPE_7__ {int iRoot; int nHeight; int /*<<< orphan*/  iTransId; } ;
typedef  TYPE_1__ TreeRoot ;
struct TYPE_8__ {scalar_t__* aiKeyPtr; } ;
typedef  TYPE_2__ TreeNode ;
struct TYPE_9__ {int iNode; scalar_t__* aiCell; TYPE_2__** apTreeNode; TYPE_1__* pRoot; int /*<<< orphan*/ * pDb; } ;
typedef  TYPE_3__ TreeCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int getChildPtr (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  treeCursorRestore (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ treeShmptr (int /*<<< orphan*/ *,int) ; 

int lsmTreeCursorEnd(TreeCursor *pCsr, int bLast){
  lsm_db *pDb = pCsr->pDb;
  TreeRoot *pRoot = pCsr->pRoot;
  int rc = LSM_OK;

  u32 iNodePtr;
  pCsr->iNode = -1;

  /* Discard any saved position data */
  treeCursorRestore(pCsr, 0);

  iNodePtr = pRoot->iRoot;
  while( iNodePtr ){
    int iCell;
    TreeNode *pNode;

    pNode = (TreeNode *)treeShmptr(pDb, iNodePtr);
    if( rc ) break;

    if( bLast ){
      iCell = ((pNode->aiKeyPtr[2]==0) ? 2 : 3);
    }else{
      iCell = ((pNode->aiKeyPtr[0]==0) ? 1 : 0);
    }
    pCsr->iNode++;
    pCsr->apTreeNode[pCsr->iNode] = pNode;

    if( (u32)pCsr->iNode<pRoot->nHeight-1 ){
      iNodePtr = getChildPtr(pNode, pRoot->iTransId, iCell);
    }else{
      iNodePtr = 0;
    }
    pCsr->aiCell[pCsr->iNode] = (u8)(iCell - (iNodePtr==0 && bLast));
  }

  return rc;
}