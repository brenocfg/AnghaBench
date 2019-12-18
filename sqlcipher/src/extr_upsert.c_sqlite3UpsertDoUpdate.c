#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_19__ {int iDataCur; int /*<<< orphan*/  pUpsertWhere; int /*<<< orphan*/  pUpsertSet; int /*<<< orphan*/  pUpsertSrc; } ;
typedef  TYPE_2__ Upsert ;
struct TYPE_20__ {TYPE_1__* aCol; } ;
typedef  TYPE_3__ Table ;
struct TYPE_22__ {int nKeyCol; size_t* aiColumn; int /*<<< orphan*/  zName; } ;
struct TYPE_21__ {int nMem; int /*<<< orphan*/ * db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_18__ {int /*<<< orphan*/  zName; } ;
typedef  int /*<<< orphan*/  SrcList ;
typedef  TYPE_4__ Parse ;
typedef  TYPE_5__ Index ;

/* Variables and functions */
 scalar_t__ HasRowid (TYPE_3__*) ; 
 int /*<<< orphan*/  OE_Abort ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_Found ; 
 int /*<<< orphan*/  OP_Halt ; 
 int /*<<< orphan*/  OP_IdxRowid ; 
 int /*<<< orphan*/  OP_SeekRowid ; 
 int /*<<< orphan*/  P4_STATIC ; 
 int /*<<< orphan*/  SQLITE_CORRUPT ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeNoopComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3ColumnOfIndex (TYPE_5__*,size_t) ; 
 int sqlite3GetTempReg (TYPE_4__*) ; 
 TYPE_5__* sqlite3PrimaryKeyIndex (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_4__*,int) ; 
 int /*<<< orphan*/ * sqlite3SrcListDup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Update (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeVerifyAbortable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sqlite3UpsertDoUpdate(
  Parse *pParse,        /* The parsing and code-generating context */
  Upsert *pUpsert,      /* The ON CONFLICT clause for the upsert */
  Table *pTab,          /* The table being updated */
  Index *pIdx,          /* The UNIQUE constraint that failed */
  int iCur              /* Cursor for pIdx (or pTab if pIdx==NULL) */
){
  Vdbe *v = pParse->pVdbe;
  sqlite3 *db = pParse->db;
  SrcList *pSrc;            /* FROM clause for the UPDATE */
  int iDataCur;

  assert( v!=0 );
  assert( pUpsert!=0 );
  VdbeNoopComment((v, "Begin DO UPDATE of UPSERT"));
  iDataCur = pUpsert->iDataCur;
  if( pIdx && iCur!=iDataCur ){
    if( HasRowid(pTab) ){
      int regRowid = sqlite3GetTempReg(pParse);
      sqlite3VdbeAddOp2(v, OP_IdxRowid, iCur, regRowid);
      sqlite3VdbeAddOp3(v, OP_SeekRowid, iDataCur, 0, regRowid);
      VdbeCoverage(v);
      sqlite3ReleaseTempReg(pParse, regRowid);
    }else{
      Index *pPk = sqlite3PrimaryKeyIndex(pTab);
      int nPk = pPk->nKeyCol;
      int iPk = pParse->nMem+1;
      int i;
      pParse->nMem += nPk;
      for(i=0; i<nPk; i++){
        int k;
        assert( pPk->aiColumn[i]>=0 );
        k = sqlite3ColumnOfIndex(pIdx, pPk->aiColumn[i]);
        sqlite3VdbeAddOp3(v, OP_Column, iCur, k, iPk+i);
        VdbeComment((v, "%s.%s", pIdx->zName,
                    pTab->aCol[pPk->aiColumn[i]].zName));
      }
      sqlite3VdbeVerifyAbortable(v, OE_Abort);
      i = sqlite3VdbeAddOp4Int(v, OP_Found, iDataCur, 0, iPk, nPk);
      VdbeCoverage(v);
      sqlite3VdbeAddOp4(v, OP_Halt, SQLITE_CORRUPT, OE_Abort, 0, 
            "corrupt database", P4_STATIC);
      sqlite3VdbeJumpHere(v, i);
    }
  }
  /* pUpsert does not own pUpsertSrc - the outer INSERT statement does.  So
  ** we have to make a copy before passing it down into sqlite3Update() */
  pSrc = sqlite3SrcListDup(db, pUpsert->pUpsertSrc, 0);
  sqlite3Update(pParse, pSrc, pUpsert->pUpsertSet,
      pUpsert->pUpsertWhere, OE_Abort, 0, 0, pUpsert);
  pUpsert->pUpsertSet = 0;    /* Will have been deleted by sqlite3Update() */
  pUpsert->pUpsertWhere = 0;  /* Will have been deleted by sqlite3Update() */
  VdbeNoopComment((v, "End DO UPDATE of UPSERT"));
}