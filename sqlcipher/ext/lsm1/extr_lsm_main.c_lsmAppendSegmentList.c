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
struct TYPE_3__ {int /*<<< orphan*/  nSize; int /*<<< orphan*/  iRoot; int /*<<< orphan*/  iLastPg; int /*<<< orphan*/  iFirst; } ;
typedef  TYPE_1__ Segment ;
typedef  int /*<<< orphan*/  LsmString ;

/* Variables and functions */
 int /*<<< orphan*/  lsmStringAppendf (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lsmAppendSegmentList(LsmString *pStr, char *zPre, Segment *pSeg){
  lsmStringAppendf(pStr, "%s{%d %d %d %d}", zPre, 
        pSeg->iFirst, pSeg->iLastPg, pSeg->iRoot, pSeg->nSize
  );
}