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
struct TYPE_8__ {int /*<<< orphan*/  pCompress; } ;
struct TYPE_7__ {scalar_t__ iLastPg; } ;
typedef  TYPE_1__ Segment ;
typedef  scalar_t__ LsmPgno ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int fsAddOffset (TYPE_2__*,TYPE_1__*,scalar_t__,int,scalar_t__*) ; 

__attribute__((used)) static int fsNextPageOffset(
  FileSystem *pFS,                /* File system object */
  Segment *pSeg,                  /* Segment to move within */
  LsmPgno iPg,                    /* Offset of current page */
  int nByte,                      /* Size of current page including headers */
  LsmPgno *piNext                 /* OUT: Offset of next page. Or zero (EOF) */
){
  LsmPgno iNext;
  int rc;

  assert( pFS->pCompress );

  rc = fsAddOffset(pFS, pSeg, iPg, nByte-1, &iNext);
  if( pSeg && iNext==pSeg->iLastPg ){
    iNext = 0;
  }else if( rc==LSM_OK ){
    rc = fsAddOffset(pFS, pSeg, iNext, 1, &iNext);
  }

  *piNext = iNext;
  return rc;
}