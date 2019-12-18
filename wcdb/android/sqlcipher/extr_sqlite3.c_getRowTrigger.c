#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int orconf; struct TYPE_13__* pNext; TYPE_2__* pTrigger; } ;
typedef  TYPE_1__ TriggerPrg ;
struct TYPE_14__ {scalar_t__ zName; } ;
typedef  TYPE_2__ Trigger ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_15__ {TYPE_1__* pTriggerPrg; } ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* codeRowTrigger (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* sqlite3ParseToplevel (TYPE_3__*) ; 
 int /*<<< orphan*/ * tableOfTrigger (TYPE_2__*) ; 

__attribute__((used)) static TriggerPrg *getRowTrigger(
  Parse *pParse,       /* Current parse context */
  Trigger *pTrigger,   /* Trigger to code */
  Table *pTab,         /* The table trigger pTrigger is attached to */
  int orconf           /* ON CONFLICT algorithm. */
){
  Parse *pRoot = sqlite3ParseToplevel(pParse);
  TriggerPrg *pPrg;

  assert( pTrigger->zName==0 || pTab==tableOfTrigger(pTrigger) );

  /* It may be that this trigger has already been coded (or is in the
  ** process of being coded). If this is the case, then an entry with
  ** a matching TriggerPrg.pTrigger field will be present somewhere
  ** in the Parse.pTriggerPrg list. Search for such an entry.  */
  for(pPrg=pRoot->pTriggerPrg; 
      pPrg && (pPrg->pTrigger!=pTrigger || pPrg->orconf!=orconf); 
      pPrg=pPrg->pNext
  );

  /* If an existing TriggerPrg could not be located, create a new one. */
  if( !pPrg ){
    pPrg = codeRowTrigger(pParse, pTrigger, pTab, orconf);
  }

  return pPrg;
}