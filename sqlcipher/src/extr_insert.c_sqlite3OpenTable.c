#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_9__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  tnum; int /*<<< orphan*/  nCol; } ;
typedef  TYPE_1__ Table ;
struct TYPE_10__ {int /*<<< orphan*/  tnum; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_2__ Index ;

/* Variables and functions */
 scalar_t__ HasRowid (TYPE_1__*) ; 
 int /*<<< orphan*/  IsVirtual (TYPE_1__*) ; 
 int OP_OpenRead ; 
 int OP_OpenWrite ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (int /*<<< orphan*/ *) ; 
 TYPE_2__* sqlite3PrimaryKeyIndex (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3TableLock (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeSetP4KeyInfo (int /*<<< orphan*/ *,TYPE_2__*) ; 

void sqlite3OpenTable(
  Parse *pParse,  /* Generate code into this VDBE */
  int iCur,       /* The cursor number of the table */
  int iDb,        /* The database index in sqlite3.aDb[] */
  Table *pTab,    /* The table to be opened */
  int opcode      /* OP_OpenRead or OP_OpenWrite */
){
  Vdbe *v;
  assert( !IsVirtual(pTab) );
  v = sqlite3GetVdbe(pParse);
  assert( opcode==OP_OpenWrite || opcode==OP_OpenRead );
  sqlite3TableLock(pParse, iDb, pTab->tnum, 
                   (opcode==OP_OpenWrite)?1:0, pTab->zName);
  if( HasRowid(pTab) ){
    sqlite3VdbeAddOp4Int(v, opcode, iCur, pTab->tnum, iDb, pTab->nCol);
    VdbeComment((v, "%s", pTab->zName));
  }else{
    Index *pPk = sqlite3PrimaryKeyIndex(pTab);
    assert( pPk!=0 );
    assert( pPk->tnum==pTab->tnum );
    sqlite3VdbeAddOp3(v, opcode, iCur, pPk->tnum, iDb);
    sqlite3VdbeSetP4KeyInfo(pParse, pPk);
    VdbeComment((v, "%s", pTab->zName));
  }
}