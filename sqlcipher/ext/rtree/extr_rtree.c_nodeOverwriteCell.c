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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {int nBytesPerCell; int nDim2; } ;
struct TYPE_8__ {int /*<<< orphan*/ * aCoord; int /*<<< orphan*/  iRowid; } ;
struct TYPE_7__ {int isDirty; int /*<<< orphan*/ * zData; } ;
typedef  TYPE_1__ RtreeNode ;
typedef  TYPE_2__ RtreeCell ;
typedef  TYPE_3__ Rtree ;

/* Variables and functions */
 int /*<<< orphan*/  writeCoord (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeInt64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nodeOverwriteCell(
  Rtree *pRtree,             /* The overall R-Tree */
  RtreeNode *pNode,          /* The node into which the cell is to be written */
  RtreeCell *pCell,          /* The cell to write */
  int iCell                  /* Index into pNode into which pCell is written */
){
  int ii;
  u8 *p = &pNode->zData[4 + pRtree->nBytesPerCell*iCell];
  p += writeInt64(p, pCell->iRowid);
  for(ii=0; ii<pRtree->nDim2; ii++){
    p += writeCoord(p, &pCell->aCoord[ii]);
  }
  pNode->isDirty = 1;
}