#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nDim2; } ;
struct TYPE_5__ {int /*<<< orphan*/ * aCoord; } ;
typedef  int /*<<< orphan*/  RtreeDValue ;
typedef  TYPE_1__ RtreeCell ;
typedef  TYPE_2__ Rtree ;

/* Variables and functions */
 scalar_t__ DCOORD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static RtreeDValue cellMargin(Rtree *pRtree, RtreeCell *p){
  RtreeDValue margin = 0;
  int ii = pRtree->nDim2 - 2;
  do{
    margin += (DCOORD(p->aCoord[ii+1]) - DCOORD(p->aCoord[ii]));
    ii -= 2;
  }while( ii>=0 );
  return margin;
}