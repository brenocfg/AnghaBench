#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* zBasis; int n; struct TYPE_12__* pHash; int /*<<< orphan*/  rCostX; int /*<<< orphan*/  rBaseCost; TYPE_3__* pRule; scalar_t__ nBasis; } ;
typedef  TYPE_2__ fuzzer_stem ;
struct TYPE_13__ {struct TYPE_13__* pNext; } ;
typedef  TYPE_3__ fuzzer_rule ;
typedef  scalar_t__ fuzzer_len ;
struct TYPE_14__ {int /*<<< orphan*/  nStem; TYPE_2__** apHash; int /*<<< orphan*/  iRuleset; TYPE_1__* pVtab; } ;
typedef  TYPE_4__ fuzzer_cursor ;
typedef  int /*<<< orphan*/  fuzzer_cost ;
struct TYPE_11__ {TYPE_3__* pRule; } ;

/* Variables and functions */
 unsigned int fuzzerHash (char*) ; 
 scalar_t__ fuzzerSkipRule (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* sqlite3_malloc64 (scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static fuzzer_stem *fuzzerNewStem(
  fuzzer_cursor *pCur,
  const char *zWord,
  fuzzer_cost rBaseCost
){
  fuzzer_stem *pNew;
  fuzzer_rule *pRule;
  unsigned int h;

  pNew = sqlite3_malloc64( sizeof(*pNew) + strlen(zWord) + 1 );
  if( pNew==0 ) return 0;
  memset(pNew, 0, sizeof(*pNew));
  pNew->zBasis = (char*)&pNew[1];
  pNew->nBasis = (fuzzer_len)strlen(zWord);
  memcpy(pNew->zBasis, zWord, pNew->nBasis+1);
  pRule = pCur->pVtab->pRule;
  while( fuzzerSkipRule(pRule, pNew, pCur->iRuleset) ){
    pRule = pRule->pNext;
  }
  pNew->pRule = pRule;
  pNew->n = -1;
  pNew->rBaseCost = pNew->rCostX = rBaseCost;
  h = fuzzerHash(pNew->zBasis);
  pNew->pHash = pCur->apHash[h];
  pCur->apHash[h] = pNew;
  pCur->nStem++;
  return pNew;
}