#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nDim2; } ;
struct TYPE_6__ {int /*<<< orphan*/ * aCoord; } ;
typedef  scalar_t__ RtreeDValue ;
typedef  TYPE_1__ RtreeCell ;
typedef  TYPE_2__ Rtree ;

/* Variables and functions */
 int /*<<< orphan*/  DCOORD (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RTREE_ZERO ; 

__attribute__((used)) static RtreeDValue cellOverlap(
  Rtree *pRtree, 
  RtreeCell *p, 
  RtreeCell *aCell, 
  int nCell
){
  int ii;
  RtreeDValue overlap = RTREE_ZERO;
  for(ii=0; ii<nCell; ii++){
    int jj;
    RtreeDValue o = (RtreeDValue)1;
    for(jj=0; jj<pRtree->nDim2; jj+=2){
      RtreeDValue x1, x2;
      x1 = MAX(DCOORD(p->aCoord[jj]), DCOORD(aCell[ii].aCoord[jj]));
      x2 = MIN(DCOORD(p->aCoord[jj+1]), DCOORD(aCell[ii].aCoord[jj+1]));
      if( x2<x1 ){
        o = (RtreeDValue)0;
        break;
      }else{
        o = o * (x2-x1);
      }
    }
    overlap += o;
  }
  return overlap;
}