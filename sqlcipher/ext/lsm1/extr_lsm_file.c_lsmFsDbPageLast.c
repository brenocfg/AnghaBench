#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ pCompress; } ;
struct TYPE_9__ {int /*<<< orphan*/  iLastPg; } ;
typedef  TYPE_1__ Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  LsmPgno ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int fsGetPageBefore (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fsPageGet (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 

int lsmFsDbPageLast(FileSystem *pFS, Segment *pSeg, Page **ppPg){
  int rc;
  LsmPgno iPg = pSeg->iLastPg;
  if( pFS->pCompress ){
    int nSpace;
    iPg++;
    do {
      nSpace = 0;
      rc = fsGetPageBefore(pFS, pSeg, iPg, &iPg);
      if( rc==LSM_OK ){
        rc = fsPageGet(pFS, pSeg, iPg, 0, ppPg, &nSpace);
      }
    }while( rc==LSM_OK && nSpace>0 );

  }else{
    rc = fsPageGet(pFS, pSeg, iPg, 0, ppPg, 0);
  }
  return rc;
}