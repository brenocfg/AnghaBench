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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_2__ {int ePhase; char const* zCurrentRow; scalar_t__ szRow; scalar_t__ pStmt; scalar_t__ nPrefix; int /*<<< orphan*/  zPrefix; int /*<<< orphan*/  db; int /*<<< orphan*/  j; int /*<<< orphan*/  iRowid; } ;
typedef  TYPE_1__ completion_cursor ;

/* Variables and functions */
#define  COMPLETION_COLUMNS 131 
#define  COMPLETION_DATABASES 130 
 int COMPLETION_EOF ; 
#define  COMPLETION_KEYWORDS 129 
#define  COMPLETION_TABLES 128 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 scalar_t__ sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_keyword_count () ; 
 int /*<<< orphan*/  sqlite3_keyword_name (int /*<<< orphan*/ ,char const**,scalar_t__*) ; 
 char* sqlite3_mprintf (char*,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_strnicmp (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

__attribute__((used)) static int completionNext(sqlite3_vtab_cursor *cur){
  completion_cursor *pCur = (completion_cursor*)cur;
  int eNextPhase = 0;  /* Next phase to try if current phase reaches end */
  int iCol = -1;       /* If >=0, step pCur->pStmt and use the i-th column */
  pCur->iRowid++;
  while( pCur->ePhase!=COMPLETION_EOF ){
    switch( pCur->ePhase ){
      case COMPLETION_KEYWORDS: {
        if( pCur->j >= sqlite3_keyword_count() ){
          pCur->zCurrentRow = 0;
          pCur->ePhase = COMPLETION_DATABASES;
        }else{
          sqlite3_keyword_name(pCur->j++, &pCur->zCurrentRow, &pCur->szRow);
        }
        iCol = -1;
        break;
      }
      case COMPLETION_DATABASES: {
        if( pCur->pStmt==0 ){
          sqlite3_prepare_v2(pCur->db, "PRAGMA database_list", -1,
                             &pCur->pStmt, 0);
        }
        iCol = 1;
        eNextPhase = COMPLETION_TABLES;
        break;
      }
      case COMPLETION_TABLES: {
        if( pCur->pStmt==0 ){
          sqlite3_stmt *pS2;
          char *zSql = 0;
          const char *zSep = "";
          sqlite3_prepare_v2(pCur->db, "PRAGMA database_list", -1, &pS2, 0);
          while( sqlite3_step(pS2)==SQLITE_ROW ){
            const char *zDb = (const char*)sqlite3_column_text(pS2, 1);
            zSql = sqlite3_mprintf(
               "%z%s"
               "SELECT name FROM \"%w\".sqlite_master",
               zSql, zSep, zDb
            );
            if( zSql==0 ) return SQLITE_NOMEM;
            zSep = " UNION ";
          }
          sqlite3_finalize(pS2);
          sqlite3_prepare_v2(pCur->db, zSql, -1, &pCur->pStmt, 0);
          sqlite3_free(zSql);
        }
        iCol = 0;
        eNextPhase = COMPLETION_COLUMNS;
        break;
      }
      case COMPLETION_COLUMNS: {
        if( pCur->pStmt==0 ){
          sqlite3_stmt *pS2;
          char *zSql = 0;
          const char *zSep = "";
          sqlite3_prepare_v2(pCur->db, "PRAGMA database_list", -1, &pS2, 0);
          while( sqlite3_step(pS2)==SQLITE_ROW ){
            const char *zDb = (const char*)sqlite3_column_text(pS2, 1);
            zSql = sqlite3_mprintf(
               "%z%s"
               "SELECT pti.name FROM \"%w\".sqlite_master AS sm"
                       " JOIN pragma_table_info(sm.name,%Q) AS pti"
               " WHERE sm.type='table'",
               zSql, zSep, zDb, zDb
            );
            if( zSql==0 ) return SQLITE_NOMEM;
            zSep = " UNION ";
          }
          sqlite3_finalize(pS2);
          sqlite3_prepare_v2(pCur->db, zSql, -1, &pCur->pStmt, 0);
          sqlite3_free(zSql);
        }
        iCol = 0;
        eNextPhase = COMPLETION_EOF;
        break;
      }
    }
    if( iCol<0 ){
      /* This case is when the phase presets zCurrentRow */
      if( pCur->zCurrentRow==0 ) continue;
    }else{
      if( sqlite3_step(pCur->pStmt)==SQLITE_ROW ){
        /* Extract the next row of content */
        pCur->zCurrentRow = (const char*)sqlite3_column_text(pCur->pStmt, iCol);
        pCur->szRow = sqlite3_column_bytes(pCur->pStmt, iCol);
      }else{
        /* When all rows are finished, advance to the next phase */
        sqlite3_finalize(pCur->pStmt);
        pCur->pStmt = 0;
        pCur->ePhase = eNextPhase;
        continue;
      }
    }
    if( pCur->nPrefix==0 ) break;
    if( pCur->nPrefix<=pCur->szRow
     && sqlite3_strnicmp(pCur->zPrefix, pCur->zCurrentRow, pCur->nPrefix)==0
    ){
      break;
    }
  }

  return SQLITE_OK;
}