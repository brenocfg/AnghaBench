#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ pVtab; } ;
typedef  TYPE_1__ sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_8__ {char* zSchema; int hasRowid; scalar_t__ pStmt; } ;
struct TYPE_7__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ BinfoTable ;
typedef  TYPE_3__ BinfoCursor ;

/* Variables and functions */
 scalar_t__ SQLITE_NULL ; 
 int SQLITE_OK ; 
 int binfoNext (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_finalize (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 void* sqlite3_mprintf (char*,...) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 char* sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int binfoFilter(
  sqlite3_vtab_cursor *pCursor, 
  int idxNum, const char *idxStr,
  int argc, sqlite3_value **argv
){
  BinfoCursor *pCsr = (BinfoCursor *)pCursor;
  BinfoTable *pTab = (BinfoTable *)pCursor->pVtab;
  char *zSql;
  int rc;

  sqlite3_free(pCsr->zSchema);
  if( idxNum==1 && sqlite3_value_type(argv[0])!=SQLITE_NULL ){
    pCsr->zSchema = sqlite3_mprintf("%s", sqlite3_value_text(argv[0]));
  }else{
    pCsr->zSchema = sqlite3_mprintf("main");
  }
  zSql = sqlite3_mprintf(
      "SELECT 0, 'table','sqlite_master','sqlite_master',1,NULL "
      "UNION ALL "
      "SELECT rowid, type, name, tbl_name, rootpage, sql"
      " FROM \"%w\".sqlite_master WHERE rootpage>=1",
       pCsr->zSchema);
  sqlite3_finalize(pCsr->pStmt);
  pCsr->pStmt = 0;
  pCsr->hasRowid = -1;
  rc = sqlite3_prepare_v2(pTab->db, zSql, -1, &pCsr->pStmt, 0);
  sqlite3_free(zSql);
  if( rc==SQLITE_OK ){
    rc = binfoNext(pCursor);
  }
  return rc;
}