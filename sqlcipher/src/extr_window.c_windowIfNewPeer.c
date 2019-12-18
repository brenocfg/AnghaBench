#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_4__ {int nExpr; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  int /*<<< orphan*/  KeyInfo ;
typedef  TYPE_1__ ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Compare ; 
 int /*<<< orphan*/  OP_Copy ; 
 int /*<<< orphan*/  OP_Goto ; 
 int /*<<< orphan*/  OP_Jump ; 
 int /*<<< orphan*/  P4_KEYINFO ; 
 int /*<<< orphan*/  VdbeCoverageEqNe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3KeyInfoFromExprList (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAppendP4 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void windowIfNewPeer(
  Parse *pParse,
  ExprList *pOrderBy,
  int regNew,                     /* First in array of new values */
  int regOld,                     /* First in array of old values */
  int addr                        /* Jump here */
){
  Vdbe *v = sqlite3GetVdbe(pParse);
  if( pOrderBy ){
    int nVal = pOrderBy->nExpr;
    KeyInfo *pKeyInfo = sqlite3KeyInfoFromExprList(pParse, pOrderBy, 0, 0);
    sqlite3VdbeAddOp3(v, OP_Compare, regOld, regNew, nVal);
    sqlite3VdbeAppendP4(v, (void*)pKeyInfo, P4_KEYINFO);
    sqlite3VdbeAddOp3(v, OP_Jump, 
      sqlite3VdbeCurrentAddr(v)+1, addr, sqlite3VdbeCurrentAddr(v)+1
    );
    VdbeCoverageEqNe(v);
    sqlite3VdbeAddOp3(v, OP_Copy, regNew, regOld, nVal-1);
  }else{
    sqlite3VdbeAddOp2(v, OP_Goto, 0, addr);
  }
}