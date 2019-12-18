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
struct TYPE_5__ {int rc; int /*<<< orphan*/  zErrmsg; int /*<<< orphan*/  dbMain; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_6__ {int /*<<< orphan*/  zIdx; } ;
typedef  TYPE_2__ RbuObjIter ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int prepareAndCollectError (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 char* rbuStrndup (char const*,int*) ; 
 int sqlite3_bind_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *rbuObjIterGetIndexWhere(sqlite3rbu *p, RbuObjIter *pIter){
  sqlite3_stmt *pStmt = 0;
  int rc = p->rc;
  char *zRet = 0;

  if( rc==SQLITE_OK ){
    rc = prepareAndCollectError(p->dbMain, &pStmt, &p->zErrmsg,
        "SELECT trim(sql) FROM sqlite_master WHERE type='index' AND name=?"
    );
  }
  if( rc==SQLITE_OK ){
    int rc2;
    rc = sqlite3_bind_text(pStmt, 1, pIter->zIdx, -1, SQLITE_STATIC);
    if( rc==SQLITE_OK && SQLITE_ROW==sqlite3_step(pStmt) ){
      const char *zSql = (const char*)sqlite3_column_text(pStmt, 0);
      if( zSql ){
        int nParen = 0;           /* Number of open parenthesis */
        int i;
        for(i=0; zSql[i]; i++){
          char c = zSql[i];
          if( c=='(' ){
            nParen++;
          }
          else if( c==')' ){
            nParen--;
            if( nParen==0 ){
              i++;
              break;
            }
          }else if( c=='"' || c=='\'' || c=='`' ){
            for(i++; 1; i++){
              if( zSql[i]==c ){
                if( zSql[i+1]!=c ) break;
                i++;
              }
            }
          }else if( c=='[' ){
            for(i++; 1; i++){
              if( zSql[i]==']' ) break;
            }
          }
        }
        if( zSql[i] ){
          zRet = rbuStrndup(&zSql[i], &rc);
        }
      }
    }

    rc2 = sqlite3_finalize(pStmt);
    if( rc==SQLITE_OK ) rc = rc2;
  }

  p->rc = rc;
  return zRet;
}