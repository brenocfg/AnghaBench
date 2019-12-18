#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nBasis; } ;
typedef  TYPE_1__ fuzzer_stem ;
struct TYPE_6__ {int iRuleset; scalar_t__ nTo; scalar_t__ nFrom; } ;
typedef  TYPE_2__ fuzzer_rule ;

/* Variables and functions */
 scalar_t__ FUZZER_MX_OUTPUT_LENGTH ; 

__attribute__((used)) static int fuzzerSkipRule(
  const fuzzer_rule *pRule,       /* Determine whether or not to skip this */
  fuzzer_stem *pStem,             /* Stem rule may be applied to */
  int iRuleset                    /* Rule-set used by the current query */
){
  return pRule && (
      (pRule->iRuleset!=iRuleset)
   || (pStem->nBasis + pRule->nTo - pRule->nFrom)>FUZZER_MX_OUTPUT_LENGTH
  );
}