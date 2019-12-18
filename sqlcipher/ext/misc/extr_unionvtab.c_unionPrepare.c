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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (char**) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sqlite3_stmt *unionPrepare(
  int *pRc,                       /* IN/OUT: Error code */
  sqlite3 *db,                    /* Database handle */
  const char *zSql,               /* SQL statement to prepare */
  char **pzErr                    /* OUT: Error message */
){
  sqlite3_stmt *pRet = 0;
  assert( pzErr );
  if( *pRc==SQLITE_OK ){
    int rc = sqlite3_prepare_v2(db, zSql, -1, &pRet, 0);
    if( rc!=SQLITE_OK ){
      *pzErr = sqlite3_mprintf("sql error: %s", sqlite3_errmsg(db));
      *pRc = rc;
    }
  }
  return pRet;
}