#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ i64 ;
struct TYPE_7__ {int /*<<< orphan*/  fdDb; int /*<<< orphan*/  pEnv; int /*<<< orphan*/  pCompress; } ;
typedef  int /*<<< orphan*/  Segment ;
typedef  TYPE_1__ FileSystem ;

/* Variables and functions */
 scalar_t__ LSM_MIN (scalar_t__,int) ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int fsBlockNext (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ fsFirstPageOnBlock (TYPE_1__*,int) ; 
 scalar_t__ fsLastPageOnPagesBlock (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  fsPageToBlock (TYPE_1__*,scalar_t__) ; 
 int lsmEnvRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fsReadData(
  FileSystem *pFS,                /* File-system handle */
  Segment *pSeg,                  /* Block redirection */
  i64 iOff,                       /* Read data from this offset */
  u8 *aData,                      /* Buffer to read data into */
  int nData                       /* Number of bytes to read */
){
  i64 iEob;                       /* End of block */
  int nRead;
  int rc;

  assert( pFS->pCompress );

  iEob = fsLastPageOnPagesBlock(pFS, iOff) + 1;
  nRead = (int)LSM_MIN(iEob - iOff, nData);

  rc = lsmEnvRead(pFS->pEnv, pFS->fdDb, iOff, aData, nRead);
  if( rc==LSM_OK && nRead!=nData ){
    int iBlk;

    rc = fsBlockNext(pFS, pSeg, fsPageToBlock(pFS, iOff), &iBlk);
    if( rc==LSM_OK ){
      i64 iOff2 = fsFirstPageOnBlock(pFS, iBlk);
      rc = lsmEnvRead(pFS->pEnv, pFS->fdDb, iOff2, &aData[nRead], nData-nRead);
    }
  }

  return rc;
}