#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_2__ {int rc; char* zSql; scalar_t__ pExplain; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ explain_cursor ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 scalar_t__ SQLITE_TEXT ; 
 int /*<<< orphan*/  sqlite3_finalize (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 void* sqlite3_mprintf (char*,char*) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int sqlite3_step (scalar_t__) ; 
 char* sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int explainFilter(
  sqlite3_vtab_cursor *pVtabCursor, 
  int idxNum, const char *idxStr,
  int argc, sqlite3_value **argv
){
  explain_cursor *pCur = (explain_cursor *)pVtabCursor;
  char *zSql = 0;
  int rc;
  sqlite3_finalize(pCur->pExplain);
  pCur->pExplain = 0;
  if( sqlite3_value_type(argv[0])!=SQLITE_TEXT ){
    pCur->rc = SQLITE_DONE;
    return SQLITE_OK;
  }
  sqlite3_free(pCur->zSql);
  pCur->zSql = sqlite3_mprintf("%s", sqlite3_value_text(argv[0]));
  if( pCur->zSql ){
    zSql = sqlite3_mprintf("EXPLAIN %s", pCur->zSql);
  }
  if( zSql==0 ){
    rc = SQLITE_NOMEM;
  }else{
    rc = sqlite3_prepare_v2(pCur->db, zSql, -1, &pCur->pExplain, 0);
    sqlite3_free(zSql);
  }
  if( rc ){
    sqlite3_finalize(pCur->pExplain);
    pCur->pExplain = 0;
    sqlite3_free(pCur->zSql);
    pCur->zSql = 0;
  }else{
    pCur->rc = sqlite3_step(pCur->pExplain);
    rc = (pCur->rc==SQLITE_DONE || pCur->rc==SQLITE_ROW) ? SQLITE_OK : pCur->rc;
  }
  return rc;
}