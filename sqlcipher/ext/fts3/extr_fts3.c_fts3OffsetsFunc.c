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
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fts3CursorSeek (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fts3FunctionArg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3Fts3Offsets (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts3OffsetsFunc(
  sqlite3_context *pContext,      /* SQLite function call context */
  int nVal,                       /* Size of argument array */
  sqlite3_value **apVal           /* Array of arguments */
){
  Fts3Cursor *pCsr;               /* Cursor handle passed through apVal[0] */

  UNUSED_PARAMETER(nVal);

  assert( nVal==1 );
  if( fts3FunctionArg(pContext, "offsets", apVal[0], &pCsr) ) return;
  assert( pCsr );
  if( SQLITE_OK==fts3CursorSeek(pContext, pCsr) ){
    sqlite3Fts3Offsets(pContext, pCsr);
  }
}