#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_12__ {int nHeight; scalar_t__ iTransId; } ;
struct TYPE_13__ {TYPE_1__ root; } ;
struct TYPE_14__ {TYPE_2__ treehdr; } ;
typedef  TYPE_3__ lsm_db ;
struct TYPE_15__ {scalar_t__ iV2; scalar_t__ iV2Ptr; scalar_t__ iV2Child; } ;
typedef  TYPE_4__ TreeNode ;
struct TYPE_16__ {size_t iNode; int /*<<< orphan*/  blob; int /*<<< orphan*/  pDb; TYPE_4__** apTreeNode; } ;
typedef  TYPE_5__ TreeCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int lsmTreeCursorEnd (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int lsmTreeCursorNext (TYPE_5__*) ; 
 scalar_t__ lsmTreeCursorValid (TYPE_5__*) ; 
 int /*<<< orphan*/  tblobFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  treeCursorInit (TYPE_3__*,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static int treeRepairPtrs(lsm_db *db){
  int rc = LSM_OK;

  if( db->treehdr.root.nHeight>1 ){
    TreeCursor csr;               /* Cursor used to iterate through tree */
    u32 iTransId = db->treehdr.root.iTransId;

    /* Initialize the cursor structure. Also decrement the nHeight variable
    ** in the tree-header. This will prevent the cursor from visiting any
    ** leaf nodes.  */
    db->treehdr.root.nHeight--;
    treeCursorInit(db, 0, &csr);

    rc = lsmTreeCursorEnd(&csr, 0);
    while( rc==LSM_OK && lsmTreeCursorValid(&csr) ){
      TreeNode *pNode = csr.apTreeNode[csr.iNode];
      if( pNode->iV2>iTransId ){
        pNode->iV2Child = 0;
        pNode->iV2Ptr = 0;
        pNode->iV2 = 0;
      }
      rc = lsmTreeCursorNext(&csr);
    }
    tblobFree(csr.pDb, &csr.blob);

    db->treehdr.root.nHeight++;
  }

  return rc;
}