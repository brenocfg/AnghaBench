#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  UnionTab ;
struct TYPE_5__ {int /*<<< orphan*/  zDb; int /*<<< orphan*/  zTab; } ;
typedef  TYPE_1__ UnionSrc ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unionFinalize (int*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * unionGetDb (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int unionIsIntkeyTable (int /*<<< orphan*/ *,TYPE_1__*,char**) ; 
 int /*<<< orphan*/ * unionPrepare (int*,int /*<<< orphan*/ *,char*,char**) ; 
 char* unionStrdup (int*,char const*) ; 

__attribute__((used)) static char *unionSourceToStr(
  int *pRc,                       /* IN/OUT: Error code */
  UnionTab *pTab,                 /* Virtual table object */
  UnionSrc *pSrc,                 /* Source table to test */
  char **pzErr                    /* OUT: Error message */
){
  char *zRet = 0;
  if( *pRc==SQLITE_OK ){
    sqlite3 *db = unionGetDb(pTab, pSrc);
    int rc = unionIsIntkeyTable(db, pSrc, pzErr);
    sqlite3_stmt *pStmt = unionPrepare(&rc, db, 
        "SELECT group_concat(quote(name) || '.' || quote(type)) "
        "FROM pragma_table_info(?, ?)", pzErr
    );
    if( rc==SQLITE_OK ){
      sqlite3_bind_text(pStmt, 1, pSrc->zTab, -1, SQLITE_STATIC);
      sqlite3_bind_text(pStmt, 2, pSrc->zDb, -1, SQLITE_STATIC);
      if( SQLITE_ROW==sqlite3_step(pStmt) ){
        const char *z = (const char*)sqlite3_column_text(pStmt, 0);
        zRet = unionStrdup(&rc, z);
      }
      unionFinalize(&rc, pStmt, pzErr);
    }
    *pRc = rc;
  }

  return zRet;
}