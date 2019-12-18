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
struct TYPE_2__ {int nBlock; scalar_t__ iInUse; } ;
typedef  TYPE_1__ DbTruncateCtx ;

/* Variables and functions */

__attribute__((used)) static int dbTruncateCb(void *pCtx, int iBlk, i64 iSnapshot){
  DbTruncateCtx *p = (DbTruncateCtx *)pCtx;
  if( iBlk!=p->nBlock || (p->iInUse>=0 && iSnapshot>=p->iInUse) ) return 1;
  p->nBlock--;
  return 0;
}