#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ pCompress; } ;
struct TYPE_8__ {scalar_t__ iPg; scalar_t__ nCompress; TYPE_5__* pFS; } ;
struct TYPE_7__ {scalar_t__ iLastPg; } ;
typedef  TYPE_1__ Segment ;
typedef  TYPE_2__ Page ;
typedef  scalar_t__ LsmPgno ;

/* Variables and functions */
 int LSM_OK ; 
 int fsNextPageOffset (TYPE_5__*,TYPE_1__*,scalar_t__,scalar_t__,scalar_t__*) ; 

int lsmFsDbPageIsLast(Segment *pSeg, Page *pPg){
  if( pPg->pFS->pCompress ){
    LsmPgno iNext = 0;
    int rc;
    rc = fsNextPageOffset(pPg->pFS, pSeg, pPg->iPg, pPg->nCompress+6, &iNext);
    return (rc!=LSM_OK || iNext==0);
  }
  return (pPg->iPg==pSeg->iLastPg);
}