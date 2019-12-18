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
typedef  int i64 ;
typedef  int /*<<< orphan*/  aNext ;
struct TYPE_11__ {scalar_t__ nMapLimit; scalar_t__ pCompress; int nBlocksize; int nPagesize; int /*<<< orphan*/  fdDb; int /*<<< orphan*/  pEnv; } ;
struct TYPE_10__ {int /*<<< orphan*/ * aData; } ;
struct TYPE_9__ {int /*<<< orphan*/  pRedirect; } ;
typedef  TYPE_1__ Segment ;
typedef  TYPE_2__ Page ;
typedef  TYPE_3__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fsPageGet (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int fsRedirectBlock (int /*<<< orphan*/ ,int) ; 
 int lsmEnvRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lsmFsPageRelease (TYPE_2__*) ; 
 int lsmGetU32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsBlockNext(
  FileSystem *pFS,                /* File-system object handle */
  Segment *pSeg,                  /* Use this segment for block redirects */
  int iBlock,                     /* Read field from this block */
  int *piNext                     /* OUT: Next block in linked list */
){
  int rc;
  int iRead;                      /* Read block from here */
  
  if( pSeg ){
    iRead = fsRedirectBlock(pSeg->pRedirect, iBlock);
  }else{
    iRead = iBlock;
  }

  assert( pFS->nMapLimit==0 || pFS->pCompress==0 );
  if( pFS->pCompress ){
    i64 iOff;                     /* File offset to read data from */
    u8 aNext[4];                  /* 4-byte pointer read from db file */

    iOff = (i64)iRead * pFS->nBlocksize - sizeof(aNext);
    rc = lsmEnvRead(pFS->pEnv, pFS->fdDb, iOff, aNext, sizeof(aNext));
    if( rc==LSM_OK ){
      *piNext = (int)lsmGetU32(aNext);
    }
  }else{
    const int nPagePerBlock = (pFS->nBlocksize / pFS->nPagesize);
    Page *pLast;
    rc = fsPageGet(pFS, 0, iRead*nPagePerBlock, 0, &pLast, 0);
    if( rc==LSM_OK ){
      *piNext = lsmGetU32(&pLast->aData[pFS->nPagesize-4]);
      lsmFsPageRelease(pLast);
    }
  }

  if( pSeg ){
    *piNext = fsRedirectBlock(pSeg->pRedirect, *piNext);
  }
  return rc;
}