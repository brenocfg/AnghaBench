#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int OE_Abort ; 
#define  OP_Ge 129 
#define  OP_Gt 128 
 int /*<<< orphan*/  OP_Halt ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_MustBeInt ; 
 int /*<<< orphan*/  P4_STATIC ; 
 int SQLITE_ERROR ; 
 int /*<<< orphan*/  VdbeCoverageIf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VdbeCoverageNeverNullIf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3GetTempReg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3MayAbort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAppendP4 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void windowCheckIntValue(Parse *pParse, int reg, int eCond){
  static const char *azErr[] = {
    "frame starting offset must be a non-negative integer",
    "frame ending offset must be a non-negative integer",
    "second argument to nth_value must be a positive integer"
  };
  static int aOp[] = { OP_Ge, OP_Ge, OP_Gt };
  Vdbe *v = sqlite3GetVdbe(pParse);
  int regZero = sqlite3GetTempReg(pParse);
  assert( eCond==0 || eCond==1 || eCond==2 );
  sqlite3VdbeAddOp2(v, OP_Integer, 0, regZero);
  sqlite3VdbeAddOp2(v, OP_MustBeInt, reg, sqlite3VdbeCurrentAddr(v)+2);
  VdbeCoverageIf(v, eCond==0);
  VdbeCoverageIf(v, eCond==1);
  VdbeCoverageIf(v, eCond==2);
  sqlite3VdbeAddOp3(v, aOp[eCond], regZero, sqlite3VdbeCurrentAddr(v)+2, reg);
  VdbeCoverageNeverNullIf(v, eCond==0);
  VdbeCoverageNeverNullIf(v, eCond==1);
  VdbeCoverageNeverNullIf(v, eCond==2);
  sqlite3MayAbort(pParse);
  sqlite3VdbeAddOp2(v, OP_Halt, SQLITE_ERROR, OE_Abort);
  sqlite3VdbeAppendP4(v, (void*)azErr[eCond], P4_STATIC);
  sqlite3ReleaseTempReg(pParse, regZero);
}