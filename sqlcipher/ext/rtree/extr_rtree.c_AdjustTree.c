#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* pParent; } ;
typedef  TYPE_1__ RtreeNode ;
typedef  int /*<<< orphan*/  RtreeCell ;
typedef  int /*<<< orphan*/  Rtree ;

/* Variables and functions */
 int /*<<< orphan*/  RTREE_IS_CORRUPT (int /*<<< orphan*/ *) ; 
 int SQLITE_CORRUPT_VTAB ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  cellContains (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cellUnion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nodeGetCell (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nodeOverwriteCell (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ nodeParentIndex (int /*<<< orphan*/ *,TYPE_1__*,int*) ; 

__attribute__((used)) static int AdjustTree(
  Rtree *pRtree,                    /* Rtree table */
  RtreeNode *pNode,                 /* Adjust ancestry of this node. */
  RtreeCell *pCell                  /* This cell was just inserted */
){
  RtreeNode *p = pNode;
  int cnt = 0;
  while( p->pParent ){
    RtreeNode *pParent = p->pParent;
    RtreeCell cell;
    int iCell;

    if( (++cnt)>1000 || nodeParentIndex(pRtree, p, &iCell)  ){
      RTREE_IS_CORRUPT(pRtree);
      return SQLITE_CORRUPT_VTAB;
    }

    nodeGetCell(pRtree, pParent, iCell, &cell);
    if( !cellContains(pRtree, &cell, pCell) ){
      cellUnion(pRtree, &cell, pCell);
      nodeOverwriteCell(pRtree, pParent, &cell, iCell);
    }
 
    p = pParent;
  }
  return SQLITE_OK;
}