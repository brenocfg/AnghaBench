#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_tokenizer ;
struct TYPE_4__ {int iLangid; char const** azCol; int nCol; int iDefaultCol; int bFts4; scalar_t__ nNest; int /*<<< orphan*/ * pTokenizer; } ;
typedef  TYPE_1__ ParseContext ;
typedef  int /*<<< orphan*/  Fts3Expr ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3ExprParse (TYPE_1__*,char const*,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int fts3ExprParseUnbalanced(
  sqlite3_tokenizer *pTokenizer,      /* Tokenizer module */
  int iLangid,                        /* Language id for tokenizer */
  char **azCol,                       /* Array of column names for fts3 table */
  int bFts4,                          /* True to allow FTS4-only syntax */
  int nCol,                           /* Number of entries in azCol[] */
  int iDefaultCol,                    /* Default column to query */
  const char *z, int n,               /* Text of MATCH query */
  Fts3Expr **ppExpr                   /* OUT: Parsed query structure */
){
  int nParsed;
  int rc;
  ParseContext sParse;

  memset(&sParse, 0, sizeof(ParseContext));
  sParse.pTokenizer = pTokenizer;
  sParse.iLangid = iLangid;
  sParse.azCol = (const char **)azCol;
  sParse.nCol = nCol;
  sParse.iDefaultCol = iDefaultCol;
  sParse.bFts4 = bFts4;
  if( z==0 ){
    *ppExpr = 0;
    return SQLITE_OK;
  }
  if( n<0 ){
    n = (int)strlen(z);
  }
  rc = fts3ExprParse(&sParse, z, n, ppExpr, &nParsed);
  assert( rc==SQLITE_OK || *ppExpr==0 );

  /* Check for mismatched parenthesis */
  if( rc==SQLITE_OK && sParse.nNest ){
    rc = SQLITE_ERROR;
  }
  
  return rc;
}