#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Trigger ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_12__ {struct TYPE_12__* pNextTo; } ;
struct TYPE_11__ {TYPE_1__* db; } ;
struct TYPE_10__ {int flags; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ FKey ;
typedef  int /*<<< orphan*/  ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  OE_Abort ; 
 int SQLITE_ForeignKeys ; 
 int /*<<< orphan*/ * fkActionTrigger (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ fkParentIsModified (int /*<<< orphan*/ *,TYPE_3__*,int*,int) ; 
 int /*<<< orphan*/  sqlite3CodeRowTriggerDirect (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* sqlite3FkReferences (int /*<<< orphan*/ *) ; 

void sqlite3FkActions(
  Parse *pParse,                  /* Parse context */
  Table *pTab,                    /* Table being updated or deleted from */
  ExprList *pChanges,             /* Change-list for UPDATE, NULL for DELETE */
  int regOld,                     /* Address of array containing old row */
  int *aChange,                   /* Array indicating UPDATEd columns (or 0) */
  int bChngRowid                  /* True if rowid is UPDATEd */
){
  /* If foreign-key support is enabled, iterate through all FKs that 
  ** refer to table pTab. If there is an action associated with the FK 
  ** for this operation (either update or delete), invoke the associated 
  ** trigger sub-program.  */
  if( pParse->db->flags&SQLITE_ForeignKeys ){
    FKey *pFKey;                  /* Iterator variable */
    for(pFKey = sqlite3FkReferences(pTab); pFKey; pFKey=pFKey->pNextTo){
      if( aChange==0 || fkParentIsModified(pTab, pFKey, aChange, bChngRowid) ){
        Trigger *pAct = fkActionTrigger(pParse, pTab, pFKey, pChanges);
        if( pAct ){
          sqlite3CodeRowTriggerDirect(pParse, pAct, pTab, regOld, OE_Abort, 0);
        }
      }
    }
  }
}