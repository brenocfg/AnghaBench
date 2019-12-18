#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_db ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_2__ {int iRet; int bNotOne; int /*<<< orphan*/  iInUse; } ;
typedef  TYPE_1__ FindFreeblockCtx ;

/* Variables and functions */
 int /*<<< orphan*/  findFreeblockCb ; 
 int lsmWalkFreelist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int findFreeblock(lsm_db *pDb, i64 iInUse, int bNotOne, int *piRet){
  int rc;                         /* Return code */
  FindFreeblockCtx ctx;           /* Context object */

  ctx.iInUse = iInUse;
  ctx.iRet = 0;
  ctx.bNotOne = bNotOne;
  rc = lsmWalkFreelist(pDb, 0, findFreeblockCb, (void *)&ctx);
  *piRet = ctx.iRet;

  return rc;
}