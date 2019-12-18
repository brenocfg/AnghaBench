#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_5__ {int /*<<< orphan*/  db; int /*<<< orphan*/  zTableName; int /*<<< orphan*/  zDbName; } ;
typedef  TYPE_1__ spellfix1_vtab ;
struct TYPE_6__ {int idxNum; int nRow; int iRow; int /*<<< orphan*/  pFullScan; TYPE_1__* pVTab; } ;
typedef  TYPE_2__ spellfix1_cursor ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  spellfix1ResetCursor (TYPE_2__*) ; 
 int sqlite3_bind_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spellfix1FilterForFullScan(
  spellfix1_cursor *pCur,
  int argc,
  sqlite3_value **argv
){
  int rc = SQLITE_OK;
  int idxNum = pCur->idxNum;
  char *zSql;
  spellfix1_vtab *pVTab = pCur->pVTab;
  spellfix1ResetCursor(pCur);
  assert( idxNum==0 || idxNum==64 );
  zSql = sqlite3_mprintf(
     "SELECT word, rank, NULL, langid, id FROM \"%w\".\"%w_vocab\"%s",
     pVTab->zDbName, pVTab->zTableName,
     ((idxNum & 64) ? " WHERE rowid=?" : "")
  );
  if( zSql==0 ) return SQLITE_NOMEM;
  rc = sqlite3_prepare_v2(pVTab->db, zSql, -1, &pCur->pFullScan, 0);
  sqlite3_free(zSql);
  if( rc==SQLITE_OK && (idxNum & 64) ){
    assert( argc==1 );
    rc = sqlite3_bind_value(pCur->pFullScan, 1, argv[0]);
  }
  pCur->nRow = pCur->iRow = 0;
  if( rc==SQLITE_OK ){
    rc = sqlite3_step(pCur->pFullScan);
    if( rc==SQLITE_ROW ){ pCur->iRow = -1; rc = SQLITE_OK; }
    if( rc==SQLITE_DONE ){ rc = SQLITE_OK; }
  }else{
    pCur->iRow = 0;
  }
  return rc;
}