#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_11__ {int nBytesPerCell; int nDim2; } ;
struct TYPE_10__ {int /*<<< orphan*/ * aCoord; int /*<<< orphan*/  iRowid; } ;
struct TYPE_9__ {int /*<<< orphan*/ * zData; } ;
typedef  TYPE_1__ RtreeNode ;
typedef  int /*<<< orphan*/  RtreeCoord ;
typedef  TYPE_2__ RtreeCell ;
typedef  TYPE_3__ Rtree ;

/* Variables and functions */
 int /*<<< orphan*/  nodeGetRowid (TYPE_3__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  readCoord (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nodeGetCell(
  Rtree *pRtree,               /* The overall R-Tree */
  RtreeNode *pNode,            /* The node containing the cell to be read */
  int iCell,                   /* Index of the cell within the node */
  RtreeCell *pCell             /* OUT: Write the cell contents here */
){
  u8 *pData;
  RtreeCoord *pCoord;
  int ii = 0;
  pCell->iRowid = nodeGetRowid(pRtree, pNode, iCell);
  pData = pNode->zData + (12 + pRtree->nBytesPerCell*iCell);
  pCoord = pCell->aCoord;
  do{
    readCoord(pData, &pCoord[ii]);
    readCoord(pData+4, &pCoord[ii+1]);
    pData += 8;
    ii += 2;
  }while( ii<pRtree->nDim2 );
}