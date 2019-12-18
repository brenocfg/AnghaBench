#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pRule; scalar_t__ rBaseCost; scalar_t__ rCostX; } ;
typedef  TYPE_2__ fuzzer_stem ;
typedef  scalar_t__ fuzzer_cost ;
struct TYPE_4__ {scalar_t__ rCost; } ;

/* Variables and functions */

__attribute__((used)) static fuzzer_cost fuzzerCost(fuzzer_stem *pStem){
  return pStem->rCostX = pStem->rBaseCost + pStem->pRule->rCost;
}