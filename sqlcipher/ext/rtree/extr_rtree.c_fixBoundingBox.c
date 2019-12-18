#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  iRowid; } ;
struct TYPE_12__ {int /*<<< orphan*/  iNode; struct TYPE_12__* pParent; } ;
typedef  TYPE_1__ RtreeNode ;
typedef  TYPE_2__ RtreeCell ;
typedef  int /*<<< orphan*/  Rtree ;

/* Variables and functions */
 int NCELL (TYPE_1__*) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  cellUnion (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  nodeGetCell (int /*<<< orphan*/ *,TYPE_1__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  nodeOverwriteCell (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int) ; 
 int nodeParentIndex (int /*<<< orphan*/ *,TYPE_1__*,int*) ; 

__attribute__((used)) static int fixBoundingBox(Rtree *pRtree, RtreeNode *pNode){
  RtreeNode *pParent = pNode->pParent;
  int rc = SQLITE_OK; 
  if( pParent ){
    int ii; 
    int nCell = NCELL(pNode);
    RtreeCell box;                            /* Bounding box for pNode */
    nodeGetCell(pRtree, pNode, 0, &box);
    for(ii=1; ii<nCell; ii++){
      RtreeCell cell;
      nodeGetCell(pRtree, pNode, ii, &cell);
      cellUnion(pRtree, &box, &cell);
    }
    box.iRowid = pNode->iNode;
    rc = nodeParentIndex(pRtree, pNode, &ii);
    if( rc==SQLITE_OK ){
      nodeOverwriteCell(pRtree, pParent, &box, ii);
      rc = fixBoundingBox(pRtree, pParent);
    }
  }
  return rc;
}