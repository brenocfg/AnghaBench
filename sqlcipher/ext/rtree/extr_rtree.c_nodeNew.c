#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {int /*<<< orphan*/  nNodeRef; scalar_t__ iNodeSize; } ;
struct TYPE_8__ {int nRef; int isDirty; struct TYPE_8__* pParent; int /*<<< orphan*/ * zData; } ;
typedef  TYPE_1__ RtreeNode ;
typedef  TYPE_2__ Rtree ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nodeReference (TYPE_1__*) ; 
 scalar_t__ sqlite3_malloc64 (scalar_t__) ; 

__attribute__((used)) static RtreeNode *nodeNew(Rtree *pRtree, RtreeNode *pParent){
  RtreeNode *pNode;
  pNode = (RtreeNode *)sqlite3_malloc64(sizeof(RtreeNode) + pRtree->iNodeSize);
  if( pNode ){
    memset(pNode, 0, sizeof(RtreeNode) + pRtree->iNodeSize);
    pNode->zData = (u8 *)&pNode[1];
    pNode->nRef = 1;
    pRtree->nNodeRef++;
    pNode->pParent = pParent;
    pNode->isDirty = 1;
    nodeReference(pParent);
  }
  return pNode;
}