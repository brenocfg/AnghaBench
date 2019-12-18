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
struct TYPE_4__ {int pPg; scalar_t__ pSeg; } ;
typedef  TYPE_1__ SegmentPtr ;
typedef  int /*<<< orphan*/  Page ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int lsmFsDbPageNext (scalar_t__,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  segmentPtrSetPage (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int segmentPtrNextPage(
  SegmentPtr *pPtr,              /* Load page into this SegmentPtr object */
  int eDir                       /* +1 for next(), -1 for prev() */
){
  Page *pNext;                   /* New page to load */
  int rc;                        /* Return code */

  assert( eDir==1 || eDir==-1 );
  assert( pPtr->pPg );
  assert( pPtr->pSeg || eDir>0 );

  rc = lsmFsDbPageNext(pPtr->pSeg, pPtr->pPg, eDir, &pNext);
  assert( rc==LSM_OK || pNext==0 );
  segmentPtrSetPage(pPtr, pNext);
  return rc;
}