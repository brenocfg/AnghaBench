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
struct TYPE_3__ {int /*<<< orphan*/  pTask; int /*<<< orphan*/  bUseThread; } ;
typedef  TYPE_1__ IncrMerger ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdbeIncrPopulateThread ; 
 int vdbeSorterCreateThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int vdbeIncrBgPopulate(IncrMerger *pIncr){
  void *p = (void*)pIncr;
  assert( pIncr->bUseThread );
  return vdbeSorterCreateThread(pIncr->pTask, vdbeIncrPopulateThread, p);
}