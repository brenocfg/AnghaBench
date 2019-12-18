#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  fulltext_vtab ;

/* Variables and functions */
 int /*<<< orphan*/  SEGDIR_SET_STMT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int sql_get_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sql_single_step (int /*<<< orphan*/ *) ; 
 int sqlite3_bind_blob (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int segdir_set(fulltext_vtab *v, int iLevel, int idx,
                      sqlite_int64 iStartBlockid,
                      sqlite_int64 iLeavesEndBlockid,
                      sqlite_int64 iEndBlockid,
                      const char *pRootData, int nRootData){
  sqlite3_stmt *s;
  int rc = sql_get_statement(v, SEGDIR_SET_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int(s, 1, iLevel);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int(s, 2, idx);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int64(s, 3, iStartBlockid);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int64(s, 4, iLeavesEndBlockid);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int64(s, 5, iEndBlockid);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_blob(s, 6, pRootData, nRootData, SQLITE_STATIC);
  if( rc!=SQLITE_OK ) return rc;

  return sql_single_step(s);
}