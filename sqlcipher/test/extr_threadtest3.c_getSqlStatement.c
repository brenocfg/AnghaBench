#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pCache; int /*<<< orphan*/  db; } ;
struct TYPE_7__ {struct TYPE_7__* pNext; int /*<<< orphan*/  pStmt; } ;
typedef  TYPE_1__ Statement ;
typedef  TYPE_2__ Sqlite ;
typedef  int /*<<< orphan*/  Error ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* sqlite3_malloc (int) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_sql (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite_error (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static Statement *getSqlStatement(
  Error *pErr,                    /* IN/OUT: Error code */
  Sqlite *pDb,                    /* Database handle */
  const char *zSql                /* SQL statement */
){
  Statement *pRet;
  int rc;

  for(pRet=pDb->pCache; pRet; pRet=pRet->pNext){
    if( 0==strcmp(sqlite3_sql(pRet->pStmt), zSql) ){
      return pRet;
    }
  }

  pRet = sqlite3_malloc(sizeof(Statement));
  rc = sqlite3_prepare_v2(pDb->db, zSql, -1, &pRet->pStmt, 0);
  if( rc!=SQLITE_OK ){
    sqlite_error(pErr, pDb, "prepare_v2");
    return 0;
  }
  assert( 0==strcmp(sqlite3_sql(pRet->pStmt), zSql) );

  pRet->pNext = pDb->pCache;
  pDb->pCache = pRet;
  return pRet;
}