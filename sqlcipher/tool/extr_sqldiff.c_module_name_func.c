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
typedef  int /*<<< orphan*/  zToken ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 char* gobble_token (char const*,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_stricmp (char*,char*) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void module_name_func(
  sqlite3_context *pCtx, 
  int nVal, sqlite3_value **apVal
){
  const char *zSql;
  char zToken[32];

  assert( nVal==1 );
  zSql = (const char*)sqlite3_value_text(apVal[0]);

  zSql = gobble_token(zSql, zToken, sizeof(zToken));
  if( zSql==0 || sqlite3_stricmp(zToken, "create") ) return;
  zSql = gobble_token(zSql, zToken, sizeof(zToken));
  if( zSql==0 || sqlite3_stricmp(zToken, "virtual") ) return;
  zSql = gobble_token(zSql, zToken, sizeof(zToken));
  if( zSql==0 || sqlite3_stricmp(zToken, "table") ) return;
  zSql = gobble_token(zSql, zToken, sizeof(zToken));
  if( zSql==0 ) return;
  zSql = gobble_token(zSql, zToken, sizeof(zToken));
  if( zSql==0 || sqlite3_stricmp(zToken, "using") ) return;
  zSql = gobble_token(zSql, zToken, sizeof(zToken));
  
  sqlite3_result_text(pCtx, zToken, -1, SQLITE_TRANSIENT);
}