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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  Fts3Cursor ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fts3FunctionArg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3Fts3Matchinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts3MatchinfoFunc(
  sqlite3_context *pContext,      /* SQLite function call context */
  int nVal,                       /* Size of argument array */
  sqlite3_value **apVal           /* Array of arguments */
){
  Fts3Cursor *pCsr;               /* Cursor handle passed through apVal[0] */
  assert( nVal==1 || nVal==2 );
  if( SQLITE_OK==fts3FunctionArg(pContext, "matchinfo", apVal[0], &pCsr) ){
    const char *zArg = 0;
    if( nVal>1 ){
      zArg = (const char *)sqlite3_value_text(apVal[1]);
    }
    sqlite3Fts3Matchinfo(pContext, pCsr, zArg);
  }
}