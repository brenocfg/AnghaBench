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
typedef  scalar_t__ i64 ;
struct TYPE_7__ {int /*<<< orphan*/  pCompress; } ;
typedef  int /*<<< orphan*/  Segment ;
typedef  TYPE_1__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int fsBlockNext (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ fsFirstPageOnBlock (TYPE_1__*,int) ; 
 scalar_t__ fsLastPageOnPagesBlock (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  fsPageToBlock (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int fsAddOffset(
  FileSystem *pFS, 
  Segment *pSeg,
  i64 iOff, 
  int iAdd, 
  i64 *piRes
){
  i64 iEob;
  int iBlk;
  int rc;

  assert( pFS->pCompress );

  iEob = fsLastPageOnPagesBlock(pFS, iOff);
  if( (iOff+iAdd)<=iEob ){
    *piRes = (iOff+iAdd);
    return LSM_OK;
  }

  rc = fsBlockNext(pFS, pSeg, fsPageToBlock(pFS, iOff), &iBlk);
  *piRes = fsFirstPageOnBlock(pFS, iBlk) + iAdd - (iEob - iOff + 1);
  return rc;
}