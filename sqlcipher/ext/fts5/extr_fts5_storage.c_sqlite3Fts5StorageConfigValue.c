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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_6__ {TYPE_1__* pConfig; int /*<<< orphan*/  pIndex; } ;
struct TYPE_5__ {int iCookie; } ;
typedef  TYPE_2__ Fts5Storage ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_STMT_REPLACE_CONFIG ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int fts5StorageGetStmt (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int sqlite3Fts5IndexSetCookie (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_value (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

int sqlite3Fts5StorageConfigValue(
  Fts5Storage *p, 
  const char *z,
  sqlite3_value *pVal,
  int iVal
){
  sqlite3_stmt *pReplace = 0;
  int rc = fts5StorageGetStmt(p, FTS5_STMT_REPLACE_CONFIG, &pReplace, 0);
  if( rc==SQLITE_OK ){
    sqlite3_bind_text(pReplace, 1, z, -1, SQLITE_STATIC);
    if( pVal ){
      sqlite3_bind_value(pReplace, 2, pVal);
    }else{
      sqlite3_bind_int(pReplace, 2, iVal);
    }
    sqlite3_step(pReplace);
    rc = sqlite3_reset(pReplace);
    sqlite3_bind_null(pReplace, 1);
  }
  if( rc==SQLITE_OK && pVal ){
    int iNew = p->pConfig->iCookie + 1;
    rc = sqlite3Fts5IndexSetCookie(p->pIndex, iNew);
    if( rc==SQLITE_OK ){
      p->pConfig->iCookie = iNew;
    }
  }
  return rc;
}