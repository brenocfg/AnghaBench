#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_16__ {int nKeyCol; int nColumn; scalar_t__* aiColumn; TYPE_1__* pTable; scalar_t__ pPartIdxWhere; scalar_t__ uniqNotNull; } ;
struct TYPE_15__ {int iSelfTab; int /*<<< orphan*/  db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_14__ {scalar_t__ pSelect; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  OP_MakeRecord ; 
 int /*<<< orphan*/  OP_RealAffinity ; 
 int /*<<< orphan*/  P4_TRANSIENT ; 
 int /*<<< orphan*/  SQLITE_JUMPIFNULL ; 
 scalar_t__ XN_EXPR ; 
 int /*<<< orphan*/  sqlite3ExprCodeLoadIndexColumn (TYPE_2__*,TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  sqlite3ExprIfFalseDup (TYPE_2__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int sqlite3GetTempRange (TYPE_2__*,int) ; 
 char* sqlite3IndexAffinityStr (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempRange (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP4 (int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeDeletePriorOpcode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeMakeLabel (TYPE_2__*) ; 

int sqlite3GenerateIndexKey(
  Parse *pParse,       /* Parsing context */
  Index *pIdx,         /* The index for which to generate a key */
  int iDataCur,        /* Cursor number from which to take column data */
  int regOut,          /* Put the new key into this register if not 0 */
  int prefixOnly,      /* Compute only a unique prefix of the key */
  int *piPartIdxLabel, /* OUT: Jump to this label to skip partial index */
  Index *pPrior,       /* Previously generated index key */
  int regPrior         /* Register holding previous generated key */
){
  Vdbe *v = pParse->pVdbe;
  int j;
  int regBase;
  int nCol;

  if( piPartIdxLabel ){
    if( pIdx->pPartIdxWhere ){
      *piPartIdxLabel = sqlite3VdbeMakeLabel(pParse);
      pParse->iSelfTab = iDataCur + 1;
      sqlite3ExprIfFalseDup(pParse, pIdx->pPartIdxWhere, *piPartIdxLabel, 
                            SQLITE_JUMPIFNULL);
      pParse->iSelfTab = 0;
    }else{
      *piPartIdxLabel = 0;
    }
  }
  nCol = (prefixOnly && pIdx->uniqNotNull) ? pIdx->nKeyCol : pIdx->nColumn;
  regBase = sqlite3GetTempRange(pParse, nCol);
  if( pPrior && (regBase!=regPrior || pPrior->pPartIdxWhere) ) pPrior = 0;
  for(j=0; j<nCol; j++){
    if( pPrior
     && pPrior->aiColumn[j]==pIdx->aiColumn[j]
     && pPrior->aiColumn[j]!=XN_EXPR
    ){
      /* This column was already computed by the previous index */
      continue;
    }
    sqlite3ExprCodeLoadIndexColumn(pParse, pIdx, iDataCur, j, regBase+j);
    /* If the column affinity is REAL but the number is an integer, then it
    ** might be stored in the table as an integer (using a compact
    ** representation) then converted to REAL by an OP_RealAffinity opcode.
    ** But we are getting ready to store this value back into an index, where
    ** it should be converted by to INTEGER again.  So omit the OP_RealAffinity
    ** opcode if it is present */
    sqlite3VdbeDeletePriorOpcode(v, OP_RealAffinity);
  }
  if( regOut ){
    sqlite3VdbeAddOp3(v, OP_MakeRecord, regBase, nCol, regOut);
    if( pIdx->pTable->pSelect ){
      const char *zAff = sqlite3IndexAffinityStr(pParse->db, pIdx);
      sqlite3VdbeChangeP4(v, -1, zAff, P4_TRANSIENT);
    }
  }
  sqlite3ReleaseTempRange(pParse, regBase, nCol);
  return regBase;
}