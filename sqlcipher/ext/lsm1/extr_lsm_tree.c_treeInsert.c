#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_13__ {int /*<<< orphan*/  nHeight; void* iRoot; } ;
struct TYPE_14__ {TYPE_1__ root; } ;
struct TYPE_15__ {TYPE_2__ treehdr; } ;
typedef  TYPE_3__ lsm_db ;
struct TYPE_16__ {int* aiKeyPtr; void** aiChildPtr; scalar_t__ iV2; } ;
typedef  TYPE_4__ TreeNode ;
struct TYPE_17__ {size_t iNode; int* aiCell; TYPE_4__** apTreeNode; } ;
typedef  TYPE_5__ TreeCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  WORKING_VERSION ; 
 int /*<<< orphan*/  assert (int) ; 
 void* getChildPtr (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* newTreeNode (TYPE_3__*,void**,int*) ; 
 int treeUpdatePtr (TYPE_3__*,TYPE_5__*,void*) ; 

__attribute__((used)) static int treeInsert(
  lsm_db *pDb,                    /* Database handle */
  TreeCursor *pCsr,               /* Cursor indicating path to insert at */
  u32 iLeftPtr,                   /* Left child pointer */
  u32 iTreeKey,                   /* Location of key to insert */
  u32 iRightPtr,                  /* Right child pointer */
  int iSlot                       /* Position to insert key into */
){
  int rc = LSM_OK;
  TreeNode *pNode = pCsr->apTreeNode[pCsr->iNode];

  /* Check if the node is currently full. If so, split pNode in two and
  ** call this function recursively to add a key to the parent. Otherwise, 
  ** insert the new key directly into pNode.  */
  assert( pNode->aiKeyPtr[1] );
  if( pNode->aiKeyPtr[0] && pNode->aiKeyPtr[2] ){
    u32 iLeft; TreeNode *pLeft;   /* New left-hand sibling node */
    u32 iRight; TreeNode *pRight; /* New right-hand sibling node */

    pLeft = newTreeNode(pDb, &iLeft, &rc);
    pRight = newTreeNode(pDb, &iRight, &rc);
    if( rc ) return rc;

    pLeft->aiChildPtr[1] = getChildPtr(pNode, WORKING_VERSION, 0);
    pLeft->aiKeyPtr[1] = pNode->aiKeyPtr[0];
    pLeft->aiChildPtr[2] = getChildPtr(pNode, WORKING_VERSION, 1);

    pRight->aiChildPtr[1] = getChildPtr(pNode, WORKING_VERSION, 2);
    pRight->aiKeyPtr[1] = pNode->aiKeyPtr[2];
    pRight->aiChildPtr[2] = getChildPtr(pNode, WORKING_VERSION, 3);

    if( pCsr->iNode==0 ){
      /* pNode is the root of the tree. Grow the tree by one level. */
      u32 iRoot; TreeNode *pRoot; /* New root node */

      pRoot = newTreeNode(pDb, &iRoot, &rc);
      pRoot->aiKeyPtr[1] = pNode->aiKeyPtr[1];
      pRoot->aiChildPtr[1] = iLeft;
      pRoot->aiChildPtr[2] = iRight;

      pDb->treehdr.root.iRoot = iRoot;
      pDb->treehdr.root.nHeight++;
    }else{

      pCsr->iNode--;
      rc = treeInsert(pDb, pCsr, 
          iLeft, pNode->aiKeyPtr[1], iRight, pCsr->aiCell[pCsr->iNode]
      );
    }

    assert( pLeft->iV2==0 );
    assert( pRight->iV2==0 );
    switch( iSlot ){
      case 0:
        pLeft->aiKeyPtr[0] = iTreeKey;
        pLeft->aiChildPtr[0] = iLeftPtr;
        if( iRightPtr ) pLeft->aiChildPtr[1] = iRightPtr;
        break;
      case 1:
        pLeft->aiChildPtr[3] = (iRightPtr ? iRightPtr : pLeft->aiChildPtr[2]);
        pLeft->aiKeyPtr[2] = iTreeKey;
        pLeft->aiChildPtr[2] = iLeftPtr;
        break;
      case 2:
        pRight->aiKeyPtr[0] = iTreeKey;
        pRight->aiChildPtr[0] = iLeftPtr;
        if( iRightPtr ) pRight->aiChildPtr[1] = iRightPtr;
        break;
      case 3:
        pRight->aiChildPtr[3] = (iRightPtr ? iRightPtr : pRight->aiChildPtr[2]);
        pRight->aiKeyPtr[2] = iTreeKey;
        pRight->aiChildPtr[2] = iLeftPtr;
        break;
    }

  }else{
    TreeNode *pNew;
    u32 *piKey;
    u32 *piChild;
    u32 iStore = 0;
    u32 iNew = 0;
    int i;

    /* Allocate a new version of node pNode. */
    pNew = newTreeNode(pDb, &iNew, &rc);
    if( rc ) return rc;

    piKey = pNew->aiKeyPtr;
    piChild = pNew->aiChildPtr;

    for(i=0; i<iSlot; i++){
      if( pNode->aiKeyPtr[i] ){
        *(piKey++) = pNode->aiKeyPtr[i];
        *(piChild++) = getChildPtr(pNode, WORKING_VERSION, i);
      }
    }

    *piKey++ = iTreeKey;
    *piChild++ = iLeftPtr;

    iStore = iRightPtr;
    for(i=iSlot; i<3; i++){
      if( pNode->aiKeyPtr[i] ){
        *(piKey++) = pNode->aiKeyPtr[i];
        *(piChild++) = iStore ? iStore : getChildPtr(pNode, WORKING_VERSION, i);
        iStore = 0;
      }
    }

    if( iStore ){
      *piChild = iStore;
    }else{
      *piChild = getChildPtr(pNode, WORKING_VERSION, 
          (pNode->aiKeyPtr[2] ? 3 : 2)
      );
    }
    pCsr->iNode--;
    rc = treeUpdatePtr(pDb, pCsr, iNew);
  }

  return rc;
}