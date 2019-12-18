#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ i64 ;
typedef  int /*<<< orphan*/  aPrev ;
struct TYPE_7__ {scalar_t__ nMapLimit; scalar_t__ pCompress; int /*<<< orphan*/  fdDb; int /*<<< orphan*/  pEnv; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pRedirect; } ;
typedef  TYPE_1__ Segment ;
typedef  int /*<<< orphan*/  Redirect ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fsFirstPageOnBlock (TYPE_2__*,int) ; 
 int fsRedirectBlock (int /*<<< orphan*/ *,int) ; 
 int lsmEnvRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ lsmGetU32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsBlockPrev(
  FileSystem *pFS,                /* File-system object handle */
  Segment *pSeg,                  /* Use this segment for block redirects */
  int iBlock,                     /* Read field from this block */
  int *piPrev                     /* OUT: Previous block in linked list */
){
  int rc = LSM_OK;                /* Return code */

  assert( pFS->nMapLimit==0 || pFS->pCompress==0 );
  assert( iBlock>0 );

  if( pFS->pCompress ){
    i64 iOff = fsFirstPageOnBlock(pFS, iBlock) - 4;
    u8 aPrev[4];                  /* 4-byte pointer read from db file */
    rc = lsmEnvRead(pFS->pEnv, pFS->fdDb, iOff, aPrev, sizeof(aPrev));
    if( rc==LSM_OK ){
      Redirect *pRedir = (pSeg ? pSeg->pRedirect : 0);
      *piPrev = fsRedirectBlock(pRedir, (int)lsmGetU32(aPrev));
    }
  }else{
    assert( 0 );
  }
  return rc;
}