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
struct TYPE_6__ {int nBytesPerCell; } ;
struct TYPE_5__ {int /*<<< orphan*/ * zData; } ;
typedef  TYPE_1__ RtreeNode ;
typedef  int /*<<< orphan*/  RtreeCoord ;
typedef  TYPE_2__ Rtree ;

/* Variables and functions */
 int /*<<< orphan*/  readCoord (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nodeGetCoord(
  Rtree *pRtree,               /* The overall R-Tree */
  RtreeNode *pNode,            /* The node from which to extract a coordinate */
  int iCell,                   /* The index of the cell within the node */
  int iCoord,                  /* Which coordinate to extract */
  RtreeCoord *pCoord           /* OUT: Space to write result to */
){
  readCoord(&pNode->zData[12 + pRtree->nBytesPerCell*iCell + 4*iCoord], pCoord);
}