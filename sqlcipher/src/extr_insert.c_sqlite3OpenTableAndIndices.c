#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_15__ {scalar_t__ pSchema; TYPE_3__* pIndex; int /*<<< orphan*/  zName; int /*<<< orphan*/  tnum; } ;
typedef  TYPE_1__ Table ;
struct TYPE_17__ {scalar_t__ pSchema; int /*<<< orphan*/  zName; int /*<<< orphan*/  tnum; struct TYPE_17__* pNext; } ;
struct TYPE_16__ {int nTab; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ Index ;

/* Variables and functions */
 scalar_t__ HasRowid (TYPE_1__*) ; 
 scalar_t__ IsPrimaryKeyIndex (TYPE_3__*) ; 
 scalar_t__ IsVirtual (TYPE_1__*) ; 
 int OP_OpenRead ; 
 int OP_OpenWrite ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3OpenTable (TYPE_2__*,int,int,TYPE_1__*,int) ; 
 int sqlite3SchemaToIndex (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3TableLock (TYPE_2__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3VdbeSetP4KeyInfo (TYPE_2__*,TYPE_3__*) ; 

int sqlite3OpenTableAndIndices(
  Parse *pParse,   /* Parsing context */
  Table *pTab,     /* Table to be opened */
  int op,          /* OP_OpenRead or OP_OpenWrite */
  u8 p5,           /* P5 value for OP_Open* opcodes (except on WITHOUT ROWID) */
  int iBase,       /* Use this for the table cursor, if there is one */
  u8 *aToOpen,     /* If not NULL: boolean for each table and index */
  int *piDataCur,  /* Write the database source cursor number here */
  int *piIdxCur    /* Write the first index cursor number here */
){
  int i;
  int iDb;
  int iDataCur;
  Index *pIdx;
  Vdbe *v;

  assert( op==OP_OpenRead || op==OP_OpenWrite );
  assert( op==OP_OpenWrite || p5==0 );
  if( IsVirtual(pTab) ){
    /* This routine is a no-op for virtual tables. Leave the output
    ** variables *piDataCur and *piIdxCur uninitialized so that valgrind
    ** can detect if they are used by mistake in the caller. */
    return 0;
  }
  iDb = sqlite3SchemaToIndex(pParse->db, pTab->pSchema);
  v = sqlite3GetVdbe(pParse);
  assert( v!=0 );
  if( iBase<0 ) iBase = pParse->nTab;
  iDataCur = iBase++;
  if( piDataCur ) *piDataCur = iDataCur;
  if( HasRowid(pTab) && (aToOpen==0 || aToOpen[0]) ){
    sqlite3OpenTable(pParse, iDataCur, iDb, pTab, op);
  }else{
    sqlite3TableLock(pParse, iDb, pTab->tnum, op==OP_OpenWrite, pTab->zName);
  }
  if( piIdxCur ) *piIdxCur = iBase;
  for(i=0, pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext, i++){
    int iIdxCur = iBase++;
    assert( pIdx->pSchema==pTab->pSchema );
    if( IsPrimaryKeyIndex(pIdx) && !HasRowid(pTab) ){
      if( piDataCur ) *piDataCur = iIdxCur;
      p5 = 0;
    }
    if( aToOpen==0 || aToOpen[i+1] ){
      sqlite3VdbeAddOp3(v, op, iIdxCur, pIdx->tnum, iDb);
      sqlite3VdbeSetP4KeyInfo(pParse, pIdx);
      sqlite3VdbeChangeP5(v, p5);
      VdbeComment((v, "%s", pIdx->zName));
    }
  }
  if( iBase>pParse->nTab ) pParse->nTab = iBase;
  return i;
}