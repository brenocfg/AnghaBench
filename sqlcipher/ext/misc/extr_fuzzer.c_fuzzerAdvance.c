#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ n; scalar_t__ nBasis; TYPE_2__ const* pRule; int /*<<< orphan*/ * zBasis; } ;
typedef  TYPE_1__ fuzzer_stem ;
struct TYPE_12__ {scalar_t__ iRuleset; scalar_t__ nFrom; struct TYPE_12__ const* pNext; int /*<<< orphan*/  zFrom; } ;
typedef  TYPE_2__ const fuzzer_rule ;
struct TYPE_13__ {scalar_t__ iRuleset; scalar_t__ rLimit; TYPE_2__ const nullRule; } ;
typedef  TYPE_3__ fuzzer_cursor ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fuzzerCost (TYPE_1__*) ; 
 int fuzzerSeen (TYPE_3__*,TYPE_1__*) ; 
 scalar_t__ fuzzerSkipRule (TYPE_2__ const*,TYPE_1__*,scalar_t__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fuzzerAdvance(fuzzer_cursor *pCur, fuzzer_stem *pStem){
  const fuzzer_rule *pRule;
  while( (pRule = pStem->pRule)!=0 ){
    assert( pRule==&pCur->nullRule || pRule->iRuleset==pCur->iRuleset );
    while( pStem->n < pStem->nBasis - pRule->nFrom ){
      pStem->n++;
      if( pRule->nFrom==0
       || memcmp(&pStem->zBasis[pStem->n], pRule->zFrom, pRule->nFrom)==0
      ){
        /* Found a rewrite case.  Make sure it is not a duplicate */
        int rc = fuzzerSeen(pCur, pStem);
        if( rc<0 ) return -1;
        if( rc==0 ){
          fuzzerCost(pStem);
          return 1;
        }
      }
    }
    pStem->n = -1;
    do{
      pRule = pRule->pNext;
    }while( fuzzerSkipRule(pRule, pStem, pCur->iRuleset) );
    pStem->pRule = pRule;
    if( pRule && fuzzerCost(pStem)>pCur->rLimit ) pStem->pRule = 0;
  }
  return 0;
}