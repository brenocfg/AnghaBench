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
struct TYPE_9__ {scalar_t__ eCoordType; int nDim2; } ;
struct TYPE_8__ {TYPE_1__* aCoord; } ;
struct TYPE_7__ {scalar_t__ f; scalar_t__ i; } ;
typedef  TYPE_1__ RtreeCoord ;
typedef  TYPE_2__ RtreeCell ;
typedef  TYPE_3__ Rtree ;

/* Variables and functions */
 scalar_t__ RTREE_COORD_INT32 ; 

__attribute__((used)) static int cellContains(Rtree *pRtree, RtreeCell *p1, RtreeCell *p2){
  int ii;
  int isInt = (pRtree->eCoordType==RTREE_COORD_INT32);
  for(ii=0; ii<pRtree->nDim2; ii+=2){
    RtreeCoord *a1 = &p1->aCoord[ii];
    RtreeCoord *a2 = &p2->aCoord[ii];
    if( (!isInt && (a2[0].f<a1[0].f || a2[1].f>a1[1].f)) 
     || ( isInt && (a2[0].i<a1[0].i || a2[1].i>a1[1].i)) 
    ){
      return 0;
    }
  }
  return 1;
}