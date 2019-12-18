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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  lsm_db ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_2__ TreeKey ;
struct TYPE_9__ {size_t iNode; size_t* aiCell; TYPE_1__** apTreeNode; int /*<<< orphan*/ * pDb; } ;
typedef  TYPE_3__ TreeCursor ;
typedef  int /*<<< orphan*/  TreeBlob ;
struct TYPE_7__ {int /*<<< orphan*/ * aiKeyPtr; } ;

/* Variables and functions */
 int LSM_CONTIGUOUS ; 
 int /*<<< orphan*/  TKV_LOADVAL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* treeShmkey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ treeShmptrUnsafe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TreeKey *csrGetKey(TreeCursor *pCsr, TreeBlob *pBlob, int *pRc){
  TreeKey *pRet;
  lsm_db *pDb = pCsr->pDb;
  u32 iPtr = pCsr->apTreeNode[pCsr->iNode]->aiKeyPtr[pCsr->aiCell[pCsr->iNode]];

  assert( iPtr );
  pRet = (TreeKey*)treeShmptrUnsafe(pDb, iPtr);
  if( !(pRet->flags & LSM_CONTIGUOUS) ){
    pRet = treeShmkey(pDb, iPtr, TKV_LOADVAL, pBlob, pRc);
  }

  return pRet;
}