#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/ * aColmask; } ;
typedef  TYPE_1__ TriggerPrg ;
struct TYPE_7__ {int const op; int tr_tm; int /*<<< orphan*/  pColumns; struct TYPE_7__* pNext; } ;
typedef  TYPE_2__ Trigger ;
typedef  int /*<<< orphan*/  Table ;
typedef  int /*<<< orphan*/  Parse ;
typedef  int /*<<< orphan*/  ExprList ;

/* Variables and functions */
 int TK_DELETE ; 
 int TK_UPDATE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ checkColumnOverlap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* getRowTrigger (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int) ; 

u32 sqlite3TriggerColmask(
  Parse *pParse,       /* Parse context */
  Trigger *pTrigger,   /* List of triggers on table pTab */
  ExprList *pChanges,  /* Changes list for any UPDATE OF triggers */
  int isNew,           /* 1 for new.* ref mask, 0 for old.* ref mask */
  int tr_tm,           /* Mask of TRIGGER_BEFORE|TRIGGER_AFTER */
  Table *pTab,         /* The table to code triggers from */
  int orconf           /* Default ON CONFLICT policy for trigger steps */
){
  const int op = pChanges ? TK_UPDATE : TK_DELETE;
  u32 mask = 0;
  Trigger *p;

  assert( isNew==1 || isNew==0 );
  for(p=pTrigger; p; p=p->pNext){
    if( p->op==op && (tr_tm&p->tr_tm)
     && checkColumnOverlap(p->pColumns,pChanges)
    ){
      TriggerPrg *pPrg;
      pPrg = getRowTrigger(pParse, p, pTab, orconf);
      if( pPrg ){
        mask |= pPrg->aColmask[isNew];
      }
    }
  }

  return mask;
}