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
struct TYPE_4__ {int /*<<< orphan*/  iNode; struct TYPE_4__* pParent; } ;
typedef  TYPE_1__ RtreeNode ;
typedef  int /*<<< orphan*/  Rtree ;

/* Variables and functions */
 int SQLITE_OK ; 
 int nodeRowidIndex (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int nodeParentIndex(Rtree *pRtree, RtreeNode *pNode, int *piIndex){
  RtreeNode *pParent = pNode->pParent;
  if( pParent ){
    return nodeRowidIndex(pRtree, pParent, pNode->iNode, piIndex);
  }
  *piIndex = -1;
  return SQLITE_OK;
}