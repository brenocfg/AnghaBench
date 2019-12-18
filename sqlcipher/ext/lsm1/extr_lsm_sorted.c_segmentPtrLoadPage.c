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
struct TYPE_4__ {int /*<<< orphan*/  pSeg; } ;
typedef  TYPE_1__ SegmentPtr ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int lsmFsDbPageGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  segmentPtrSetPage (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int segmentPtrLoadPage(
  FileSystem *pFS,
  SegmentPtr *pPtr,              /* Load page into this SegmentPtr object */
  int iNew                       /* Page number of new page */
){
  Page *pPg = 0;                 /* The new page */
  int rc;                        /* Return Code */

  rc = lsmFsDbPageGet(pFS, pPtr->pSeg, iNew, &pPg);
  assert( rc==LSM_OK || pPg==0 );
  segmentPtrSetPage(pPtr, pPg);

  return rc;
}