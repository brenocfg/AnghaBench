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
struct TYPE_4__ {int /*<<< orphan*/ ** aNode; int /*<<< orphan*/ * aPoint; } ;
typedef  int /*<<< orphan*/  RtreeSearchPoint ;
typedef  int /*<<< orphan*/  RtreeNode ;
typedef  TYPE_1__ RtreeCursor ;

/* Variables and functions */
 int RTREE_CACHE_SZ ; 
 int /*<<< orphan*/  RTREE_OF_CURSOR (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nodeRelease (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtreeSearchPointSwap(RtreeCursor *p, int i, int j){
  RtreeSearchPoint t = p->aPoint[i];
  assert( i<j );
  p->aPoint[i] = p->aPoint[j];
  p->aPoint[j] = t;
  i++; j++;
  if( i<RTREE_CACHE_SZ ){
    if( j>=RTREE_CACHE_SZ ){
      nodeRelease(RTREE_OF_CURSOR(p), p->aNode[i]);
      p->aNode[i] = 0;
    }else{
      RtreeNode *pTemp = p->aNode[i];
      p->aNode[i] = p->aNode[j];
      p->aNode[j] = pTemp;
    }
  }
}