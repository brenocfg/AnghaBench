#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pEnv; int /*<<< orphan*/  pFS; int /*<<< orphan*/  xLog; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_13__ {scalar_t__ iFirst; } ;
typedef  TYPE_2__ Segment ;
typedef  int /*<<< orphan*/  Page ;

/* Variables and functions */
 int INFO_PAGE_DUMP_VALUES ; 
 int /*<<< orphan*/  LSM_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infoPageDump (TYPE_1__*,int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lsmFsDbPageGet (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lsmFsDbPageNext (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lsmFsPageNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmFsPageRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmLogMessage (TYPE_1__*,int /*<<< orphan*/ ,char*,char*) ; 
 char* segToString (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sortedDumpPage (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int) ; 

void sortedDumpSegment(lsm_db *pDb, Segment *pRun, int bVals){
  assert( pDb->xLog );
  if( pRun && pRun->iFirst ){
    int flags = (bVals ? INFO_PAGE_DUMP_VALUES : 0);
    char *zSeg;
    Page *pPg;

    zSeg = segToString(pDb->pEnv, pRun, 0);
    lsmLogMessage(pDb, LSM_OK, "Segment: %s", zSeg);
    lsmFree(pDb->pEnv, zSeg);

    lsmFsDbPageGet(pDb->pFS, pRun, pRun->iFirst, &pPg);
    while( pPg ){
      Page *pNext;
      char *z = 0;
      infoPageDump(pDb, lsmFsPageNumber(pPg), flags, &z);
      lsmLogMessage(pDb, LSM_OK, "%s", z);
      lsmFree(pDb->pEnv, z);
#if 0
      sortedDumpPage(pDb, pRun, pPg, bVals);
#endif
      lsmFsDbPageNext(pRun, pPg, 1, &pNext);
      lsmFsPageRelease(pPg);
      pPg = pNext;
    }
  }
}