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
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fts3CursorSeek (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fts3FunctionArg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3Fts3Snippet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,int,int) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts3SnippetFunc(
  sqlite3_context *pContext,      /* SQLite function call context */
  int nVal,                       /* Size of apVal[] array */
  sqlite3_value **apVal           /* Array of arguments */
){
  Fts3Cursor *pCsr;               /* Cursor handle passed through apVal[0] */
  const char *zStart = "<b>";
  const char *zEnd = "</b>";
  const char *zEllipsis = "<b>...</b>";
  int iCol = -1;
  int nToken = 15;                /* Default number of tokens in snippet */

  /* There must be at least one argument passed to this function (otherwise
  ** the non-overloaded version would have been called instead of this one).
  */
  assert( nVal>=1 );

  if( nVal>6 ){
    sqlite3_result_error(pContext, 
        "wrong number of arguments to function snippet()", -1);
    return;
  }
  if( fts3FunctionArg(pContext, "snippet", apVal[0], &pCsr) ) return;

  switch( nVal ){
    case 6: nToken = sqlite3_value_int(apVal[5]);
    case 5: iCol = sqlite3_value_int(apVal[4]);
    case 4: zEllipsis = (const char*)sqlite3_value_text(apVal[3]);
    case 3: zEnd = (const char*)sqlite3_value_text(apVal[2]);
    case 2: zStart = (const char*)sqlite3_value_text(apVal[1]);
  }
  if( !zEllipsis || !zEnd || !zStart ){
    sqlite3_result_error_nomem(pContext);
  }else if( nToken==0 ){
    sqlite3_result_text(pContext, "", -1, SQLITE_STATIC);
  }else if( SQLITE_OK==fts3CursorSeek(pContext, pCsr) ){
    sqlite3Fts3Snippet(pContext, pCsr, zStart, zEnd, zEllipsis, iCol, nToken);
  }
}