#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
typedef  TYPE_2__ TreeKey ;
struct TYPE_7__ {size_t iNode; size_t* aiCell; TYPE_1__** apTreeNode; int /*<<< orphan*/  pDb; } ;
typedef  TYPE_3__ TreeCursor ;
struct TYPE_5__ {int /*<<< orphan*/ * aiKeyPtr; } ;

/* Variables and functions */
 int LSM_CONTIGUOUS ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ treeShmptrUnsafe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lsmTreeCursorFlags(TreeCursor *pCsr){
  int flags = 0;
  if( pCsr && pCsr->iNode>=0 ){
    int rc = LSM_OK;
    TreeKey *pKey = (TreeKey *)treeShmptrUnsafe(pCsr->pDb,
        pCsr->apTreeNode[pCsr->iNode]->aiKeyPtr[pCsr->aiCell[pCsr->iNode]]
    );
    assert( rc==LSM_OK );
    flags = (pKey->flags & ~LSM_CONTIGUOUS);
  }
  return flags;
}