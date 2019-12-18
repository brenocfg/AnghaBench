#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ pSchema; scalar_t__ pTabSchema; int op; int tr_tm; int /*<<< orphan*/  pColumns; struct TYPE_11__* pNext; } ;
typedef  TYPE_3__ Trigger ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_12__ {TYPE_2__* db; } ;
struct TYPE_10__ {TYPE_1__* aDb; } ;
struct TYPE_9__ {scalar_t__ pSchema; } ;
typedef  TYPE_4__ Parse ;
typedef  int /*<<< orphan*/  ExprList ;

/* Variables and functions */
 int TK_DELETE ; 
 int TK_INSERT ; 
 int TK_UPDATE ; 
 int TRIGGER_AFTER ; 
 int TRIGGER_BEFORE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ checkColumnOverlap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3CodeRowTriggerDirect (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *,int,int,int) ; 

void sqlite3CodeRowTrigger(
  Parse *pParse,       /* Parse context */
  Trigger *pTrigger,   /* List of triggers on table pTab */
  int op,              /* One of TK_UPDATE, TK_INSERT, TK_DELETE */
  ExprList *pChanges,  /* Changes list for any UPDATE OF triggers */
  int tr_tm,           /* One of TRIGGER_BEFORE, TRIGGER_AFTER */
  Table *pTab,         /* The table to code triggers from */
  int reg,             /* The first in an array of registers (see above) */
  int orconf,          /* ON CONFLICT policy */
  int ignoreJump       /* Instruction to jump to for RAISE(IGNORE) */
){
  Trigger *p;          /* Used to iterate through pTrigger list */

  assert( op==TK_UPDATE || op==TK_INSERT || op==TK_DELETE );
  assert( tr_tm==TRIGGER_BEFORE || tr_tm==TRIGGER_AFTER );
  assert( (op==TK_UPDATE)==(pChanges!=0) );

  for(p=pTrigger; p; p=p->pNext){

    /* Sanity checking:  The schema for the trigger and for the table are
    ** always defined.  The trigger must be in the same schema as the table
    ** or else it must be a TEMP trigger. */
    assert( p->pSchema!=0 );
    assert( p->pTabSchema!=0 );
    assert( p->pSchema==p->pTabSchema 
         || p->pSchema==pParse->db->aDb[1].pSchema );

    /* Determine whether we should code this trigger */
    if( p->op==op 
     && p->tr_tm==tr_tm 
     && checkColumnOverlap(p->pColumns, pChanges)
    ){
      sqlite3CodeRowTriggerDirect(pParse, p, pTab, reg, orconf, ignoreJump);
    }
  }
}