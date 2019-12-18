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
typedef  int /*<<< orphan*/  sqlite3_tokenizer ;
typedef  int /*<<< orphan*/  Fts3Expr ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 char const* SQLITE_FTS3_MAX_EXPR_DEPTH ; 
 int SQLITE_OK ; 
 int SQLITE_TOOBIG ; 
 int fts3ExprBalance (int /*<<< orphan*/ **,char const*) ; 
 int fts3ExprCheckDepth (int /*<<< orphan*/ *,char const*) ; 
 int fts3ExprParseUnbalanced (int /*<<< orphan*/ *,int,char**,int,int,int,char const*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3Fts3ErrMsg (char**,char*,char const*) ; 
 int /*<<< orphan*/  sqlite3Fts3ExprFree (int /*<<< orphan*/ *) ; 

int sqlite3Fts3ExprParse(
  sqlite3_tokenizer *pTokenizer,      /* Tokenizer module */
  int iLangid,                        /* Language id for tokenizer */
  char **azCol,                       /* Array of column names for fts3 table */
  int bFts4,                          /* True to allow FTS4-only syntax */
  int nCol,                           /* Number of entries in azCol[] */
  int iDefaultCol,                    /* Default column to query */
  const char *z, int n,               /* Text of MATCH query */
  Fts3Expr **ppExpr,                  /* OUT: Parsed query structure */
  char **pzErr                        /* OUT: Error message (sqlite3_malloc) */
){
  int rc = fts3ExprParseUnbalanced(
      pTokenizer, iLangid, azCol, bFts4, nCol, iDefaultCol, z, n, ppExpr
  );
  
  /* Rebalance the expression. And check that its depth does not exceed
  ** SQLITE_FTS3_MAX_EXPR_DEPTH.  */
  if( rc==SQLITE_OK && *ppExpr ){
    rc = fts3ExprBalance(ppExpr, SQLITE_FTS3_MAX_EXPR_DEPTH);
    if( rc==SQLITE_OK ){
      rc = fts3ExprCheckDepth(*ppExpr, SQLITE_FTS3_MAX_EXPR_DEPTH);
    }
  }

  if( rc!=SQLITE_OK ){
    sqlite3Fts3ExprFree(*ppExpr);
    *ppExpr = 0;
    if( rc==SQLITE_TOOBIG ){
      sqlite3Fts3ErrMsg(pzErr,
          "FTS expression tree is too large (maximum depth %d)", 
          SQLITE_FTS3_MAX_EXPR_DEPTH
      );
      rc = SQLITE_ERROR;
    }else if( rc==SQLITE_ERROR ){
      sqlite3Fts3ErrMsg(pzErr, "malformed MATCH expression: [%s]", z);
    }
  }

  return rc;
}