#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sParse ;
struct TYPE_20__ {int nCol; int* aiCol; } ;
struct TYPE_19__ {int nCol; } ;
struct TYPE_18__ {int /*<<< orphan*/  nPhrase; scalar_t__ apExprPhrase; TYPE_4__* pConfig; scalar_t__ pIndex; TYPE_2__* pRoot; } ;
struct TYPE_17__ {int bEof; } ;
struct TYPE_16__ {scalar_t__ rc; char* zErr; scalar_t__ apPhrase; TYPE_2__* pExpr; int /*<<< orphan*/  nPhrase; TYPE_4__* pConfig; } ;
typedef  int /*<<< orphan*/  Fts5Token ;
typedef  TYPE_1__ Fts5Parse ;
typedef  TYPE_2__ Fts5ExprNode ;
typedef  TYPE_3__ Fts5Expr ;
typedef  TYPE_4__ Fts5Config ;
typedef  TYPE_5__ Fts5Colset ;

/* Variables and functions */
 int FTS5_EOF ; 
 int SQLITE_NOMEM ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts5ExprGetToken (TYPE_1__*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5ParseAlloc ; 
 int /*<<< orphan*/  fts5ParseFree ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3Fts5MallocZero (scalar_t__*,int const) ; 
 int /*<<< orphan*/  sqlite3Fts5ParseNodeFree (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3Fts5ParseSetColset (TYPE_1__*,TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3Fts5Parser (void*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* sqlite3Fts5ParserAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Fts5ParserFree (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 TYPE_3__* sqlite3_malloc (int) ; 

int sqlite3Fts5ExprNew(
  Fts5Config *pConfig,            /* FTS5 Configuration */
  int iCol,
  const char *zExpr,              /* Expression text */
  Fts5Expr **ppNew, 
  char **pzErr
){
  Fts5Parse sParse;
  Fts5Token token;
  const char *z = zExpr;
  int t;                          /* Next token type */
  void *pEngine;
  Fts5Expr *pNew;

  *ppNew = 0;
  *pzErr = 0;
  memset(&sParse, 0, sizeof(sParse));
  pEngine = sqlite3Fts5ParserAlloc(fts5ParseAlloc);
  if( pEngine==0 ){ return SQLITE_NOMEM; }
  sParse.pConfig = pConfig;

  do {
    t = fts5ExprGetToken(&sParse, &z, &token);
    sqlite3Fts5Parser(pEngine, t, token, &sParse);
  }while( sParse.rc==SQLITE_OK && t!=FTS5_EOF );
  sqlite3Fts5ParserFree(pEngine, fts5ParseFree);

  /* If the LHS of the MATCH expression was a user column, apply the
  ** implicit column-filter.  */
  if( iCol<pConfig->nCol && sParse.pExpr && sParse.rc==SQLITE_OK ){
    int n = sizeof(Fts5Colset);
    Fts5Colset *pColset = (Fts5Colset*)sqlite3Fts5MallocZero(&sParse.rc, n);
    if( pColset ){
      pColset->nCol = 1;
      pColset->aiCol[0] = iCol;
      sqlite3Fts5ParseSetColset(&sParse, sParse.pExpr, pColset);
    }
  }

  assert( sParse.rc!=SQLITE_OK || sParse.zErr==0 );
  if( sParse.rc==SQLITE_OK ){
    *ppNew = pNew = sqlite3_malloc(sizeof(Fts5Expr));
    if( pNew==0 ){
      sParse.rc = SQLITE_NOMEM;
      sqlite3Fts5ParseNodeFree(sParse.pExpr);
    }else{
      if( !sParse.pExpr ){
        const int nByte = sizeof(Fts5ExprNode);
        pNew->pRoot = (Fts5ExprNode*)sqlite3Fts5MallocZero(&sParse.rc, nByte);
        if( pNew->pRoot ){
          pNew->pRoot->bEof = 1;
        }
      }else{
        pNew->pRoot = sParse.pExpr;
      }
      pNew->pIndex = 0;
      pNew->pConfig = pConfig;
      pNew->apExprPhrase = sParse.apPhrase;
      pNew->nPhrase = sParse.nPhrase;
      sParse.apPhrase = 0;
    }
  }else{
    sqlite3Fts5ParseNodeFree(sParse.pExpr);
  }

  sqlite3_free(sParse.apPhrase);
  *pzErr = sParse.zErr;
  return sParse.rc;
}