#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_3__ {scalar_t__ n; } ;
typedef  TYPE_1__ LsmString ;

/* Variables and functions */
 int /*<<< orphan*/  lsmStringAppendf (TYPE_1__*,char*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int infoFreelistCb(void *pCtx, int iBlk, i64 iSnapshot){
  LsmString *pStr = (LsmString *)pCtx;
  lsmStringAppendf(pStr, "%s{%d %lld}", (pStr->n?" ":""), iBlk, iSnapshot);
  return 0;
}