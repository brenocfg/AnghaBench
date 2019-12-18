#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int flags; } ;
typedef  TYPE_1__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_15__ {scalar_t__ pSelect; TYPE_4__* pFKey; } ;
typedef  TYPE_2__ Table ;
struct TYPE_17__ {scalar_t__ isDeferred; struct TYPE_17__* pNextFrom; } ;
struct TYPE_16__ {int disableTriggers; TYPE_1__* db; } ;
typedef  int /*<<< orphan*/  SrcList ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ FKey ;

/* Variables and functions */
 int /*<<< orphan*/  IsVirtual (TYPE_2__*) ; 
 int /*<<< orphan*/  OE_Abort ; 
 int /*<<< orphan*/  OP_FkIfZero ; 
 int /*<<< orphan*/  P4_STATIC ; 
 int /*<<< orphan*/  P5_ConstraintFK ; 
 int /*<<< orphan*/  SQLITE_CONSTRAINT_FOREIGNKEY ; 
 int SQLITE_DeferFKs ; 
 int SQLITE_ForeignKeys ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3DeleteFrom (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3FkReferences (TYPE_2__*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3HaltConstraint (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListDup (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int sqlite3VdbeMakeLabel (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeVerifyAbortable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sqlite3FkDropTable(Parse *pParse, SrcList *pName, Table *pTab){
  sqlite3 *db = pParse->db;
  if( (db->flags&SQLITE_ForeignKeys) && !IsVirtual(pTab) ){
    int iSkip = 0;
    Vdbe *v = sqlite3GetVdbe(pParse);

    assert( v );                  /* VDBE has already been allocated */
    assert( pTab->pSelect==0 );   /* Not a view */
    if( sqlite3FkReferences(pTab)==0 ){
      /* Search for a deferred foreign key constraint for which this table
      ** is the child table. If one cannot be found, return without 
      ** generating any VDBE code. If one can be found, then jump over
      ** the entire DELETE if there are no outstanding deferred constraints
      ** when this statement is run.  */
      FKey *p;
      for(p=pTab->pFKey; p; p=p->pNextFrom){
        if( p->isDeferred || (db->flags & SQLITE_DeferFKs) ) break;
      }
      if( !p ) return;
      iSkip = sqlite3VdbeMakeLabel(pParse);
      sqlite3VdbeAddOp2(v, OP_FkIfZero, 1, iSkip); VdbeCoverage(v);
    }

    pParse->disableTriggers = 1;
    sqlite3DeleteFrom(pParse, sqlite3SrcListDup(db, pName, 0), 0, 0, 0);
    pParse->disableTriggers = 0;

    /* If the DELETE has generated immediate foreign key constraint 
    ** violations, halt the VDBE and return an error at this point, before
    ** any modifications to the schema are made. This is because statement
    ** transactions are not able to rollback schema changes.  
    **
    ** If the SQLITE_DeferFKs flag is set, then this is not required, as
    ** the statement transaction will not be rolled back even if FK
    ** constraints are violated.
    */
    if( (db->flags & SQLITE_DeferFKs)==0 ){
      sqlite3VdbeVerifyAbortable(v, OE_Abort);
      sqlite3VdbeAddOp2(v, OP_FkIfZero, 0, sqlite3VdbeCurrentAddr(v)+2);
      VdbeCoverage(v);
      sqlite3HaltConstraint(pParse, SQLITE_CONSTRAINT_FOREIGNKEY,
          OE_Abort, 0, P4_STATIC, P5_ConstraintFK);
    }

    if( iSkip ){
      sqlite3VdbeResolveLabel(v, iSkip);
    }
  }
}