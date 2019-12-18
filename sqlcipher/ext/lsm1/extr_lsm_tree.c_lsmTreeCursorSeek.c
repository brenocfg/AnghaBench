#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  lsm_db ;
struct TYPE_14__ {scalar_t__ iRoot; int nHeight; int /*<<< orphan*/  iTransId; } ;
typedef  TYPE_1__ TreeRoot ;
struct TYPE_15__ {scalar_t__* aiKeyPtr; } ;
typedef  TYPE_2__ TreeNode ;
struct TYPE_16__ {int flags; int /*<<< orphan*/  nKey; } ;
typedef  TYPE_3__ TreeKey ;
struct TYPE_17__ {int iNode; int* aiCell; TYPE_2__** apTreeNode; TYPE_1__* pRoot; int /*<<< orphan*/ * pDb; } ;
typedef  TYPE_4__ TreeCursor ;
struct TYPE_18__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ TreeBlob ;

/* Variables and functions */
 int LSM_CONTIGUOUS ; 
 int LSM_OK ; 
 int /*<<< orphan*/  TKV_LOADKEY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ getChildPtr (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lsmTreeCursorValid (TYPE_4__*) ; 
 int /*<<< orphan*/  tblobFree (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int treeCsrCompare (TYPE_4__*,void*,int,int*) ; 
 int /*<<< orphan*/  treeCursorRestore (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int treeKeycmp (void*,int /*<<< orphan*/ ,void*,int) ; 
 TYPE_3__* treeShmkey (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,TYPE_5__*,int*) ; 
 scalar_t__ treeShmptrUnsafe (int /*<<< orphan*/ *,scalar_t__) ; 

int lsmTreeCursorSeek(TreeCursor *pCsr, void *pKey, int nKey, int *pRes){
  int rc = LSM_OK;                /* Return code */
  lsm_db *pDb = pCsr->pDb;
  TreeRoot *pRoot = pCsr->pRoot;
  u32 iNodePtr;                   /* Location of current node in search */

  /* Discard any saved position data */
  treeCursorRestore(pCsr, 0);

  iNodePtr = pRoot->iRoot;
  if( iNodePtr==0 ){
    /* Either an error occurred or the tree is completely empty. */
    assert( rc!=LSM_OK || pRoot->iRoot==0 );
    *pRes = -1;
    pCsr->iNode = -1;
  }else{
    TreeBlob b = {0, 0};
    int res = 0;                  /* Result of comparison function */
    int iNode = -1;
    while( iNodePtr ){
      TreeNode *pNode;            /* Node at location iNodePtr */
      int iTest;                  /* Index of second key to test (0 or 2) */
      u32 iTreeKey;
      TreeKey *pTreeKey;          /* Key to compare against */

      pNode = (TreeNode *)treeShmptrUnsafe(pDb, iNodePtr);
      iNode++;
      pCsr->apTreeNode[iNode] = pNode;

      /* Compare (pKey/nKey) with the key in the middle slot of B-tree node
      ** pNode. The middle slot is never empty. If the comparison is a match,
      ** then the search is finished. Break out of the loop. */
      pTreeKey = (TreeKey*)treeShmptrUnsafe(pDb, pNode->aiKeyPtr[1]);
      if( !(pTreeKey->flags & LSM_CONTIGUOUS) ){
        pTreeKey = treeShmkey(pDb, pNode->aiKeyPtr[1], TKV_LOADKEY, &b, &rc);
        if( rc!=LSM_OK ) break;
      }
      res = treeKeycmp((void *)&pTreeKey[1], pTreeKey->nKey, pKey, nKey);
      if( res==0 ){
        pCsr->aiCell[iNode] = 1;
        break;
      }

      /* Based on the results of the previous comparison, compare (pKey/nKey)
      ** to either the left or right key of the B-tree node, if such a key
      ** exists. */
      iTest = (res>0 ? 0 : 2);
      iTreeKey = pNode->aiKeyPtr[iTest];
      if( iTreeKey ){
        pTreeKey = (TreeKey*)treeShmptrUnsafe(pDb, iTreeKey);
        if( !(pTreeKey->flags & LSM_CONTIGUOUS) ){
          pTreeKey = treeShmkey(pDb, iTreeKey, TKV_LOADKEY, &b, &rc);
          if( rc ) break;
        }
        res = treeKeycmp((void *)&pTreeKey[1], pTreeKey->nKey, pKey, nKey);
        if( res==0 ){
          pCsr->aiCell[iNode] = (u8)iTest;
          break;
        }
      }else{
        iTest = 1;
      }

      if( (u32)iNode<(pRoot->nHeight-1) ){
        iNodePtr = getChildPtr(pNode, pRoot->iTransId, iTest + (res<0));
      }else{
        iNodePtr = 0;
      }
      pCsr->aiCell[iNode] = (u8)(iTest + (iNodePtr && (res<0)));
    }

    *pRes = res;
    pCsr->iNode = iNode;
    tblobFree(pDb, &b);
  }

  /* assert() that *pRes has been set properly */
#ifndef NDEBUG
  if( rc==LSM_OK && lsmTreeCursorValid(pCsr) ){
    int cmp = treeCsrCompare(pCsr, pKey, nKey, &rc);
    assert( rc!=LSM_OK || *pRes==cmp || (*pRes ^ cmp)>0 );
  }
#endif

  return rc;
}