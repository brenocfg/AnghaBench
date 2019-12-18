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
typedef  scalar_t__ i64 ;
struct TYPE_2__ {scalar_t__ iInUse; scalar_t__ bNotOne; int iRet; } ;
typedef  TYPE_1__ FindFreeblockCtx ;

/* Variables and functions */

__attribute__((used)) static int findFreeblockCb(void *pCtx, int iBlk, i64 iSnapshot){
  FindFreeblockCtx *p = (FindFreeblockCtx *)pCtx;
  if( iSnapshot<p->iInUse && (iBlk!=1 || p->bNotOne==0) ){
    p->iRet = iBlk;
    return 1;
  }
  return 0;
}