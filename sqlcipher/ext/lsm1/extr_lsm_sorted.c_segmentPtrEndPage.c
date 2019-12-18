#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  iFirst; } ;
struct TYPE_7__ {TYPE_2__* pSeg; } ;
typedef  TYPE_1__ SegmentPtr ;
typedef  TYPE_2__ Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int lsmFsDbPageGet (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int lsmFsDbPageLast (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  segmentPtrSetPage (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void segmentPtrEndPage(
  FileSystem *pFS, 
  SegmentPtr *pPtr, 
  int bLast, 
  int *pRc
){
  if( *pRc==LSM_OK ){
    Segment *pSeg = pPtr->pSeg;
    Page *pNew = 0;
    if( bLast ){
      *pRc = lsmFsDbPageLast(pFS, pSeg, &pNew);
    }else{
      *pRc = lsmFsDbPageGet(pFS, pSeg, pSeg->iFirst, &pNew);
    }
    segmentPtrSetPage(pPtr, pNew);
  }
}