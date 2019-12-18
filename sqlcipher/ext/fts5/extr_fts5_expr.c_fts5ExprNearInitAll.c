#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ bDesc; int /*<<< orphan*/  pIndex; } ;
struct TYPE_11__ {int nPhrase; int /*<<< orphan*/  pColset; TYPE_2__** apPhrase; } ;
struct TYPE_10__ {scalar_t__ bNomatch; int bEof; TYPE_4__* pNear; } ;
struct TYPE_9__ {scalar_t__ nTerm; TYPE_1__* aTerm; } ;
struct TYPE_8__ {scalar_t__ pIter; scalar_t__ bPrefix; int /*<<< orphan*/  zTerm; struct TYPE_8__* pSynonym; } ;
typedef  TYPE_1__ Fts5ExprTerm ;
typedef  TYPE_2__ Fts5ExprPhrase ;
typedef  TYPE_3__ Fts5ExprNode ;
typedef  TYPE_4__ Fts5ExprNearset ;
typedef  TYPE_5__ Fts5Expr ;

/* Variables and functions */
 int FTS5INDEX_QUERY_DESC ; 
 int FTS5INDEX_QUERY_PREFIX ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3Fts5IndexQuery (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  sqlite3Fts5IterClose (scalar_t__) ; 
 scalar_t__ sqlite3Fts5IterEof (scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5ExprNearInitAll(
  Fts5Expr *pExpr,
  Fts5ExprNode *pNode
){
  Fts5ExprNearset *pNear = pNode->pNear;
  int i;

  assert( pNode->bNomatch==0 );
  for(i=0; i<pNear->nPhrase; i++){
    Fts5ExprPhrase *pPhrase = pNear->apPhrase[i];
    if( pPhrase->nTerm==0 ){
      pNode->bEof = 1;
      return SQLITE_OK;
    }else{
      int j;
      for(j=0; j<pPhrase->nTerm; j++){
        Fts5ExprTerm *pTerm = &pPhrase->aTerm[j];
        Fts5ExprTerm *p;
        int bHit = 0;

        for(p=pTerm; p; p=p->pSynonym){
          int rc;
          if( p->pIter ){
            sqlite3Fts5IterClose(p->pIter);
            p->pIter = 0;
          }
          rc = sqlite3Fts5IndexQuery(
              pExpr->pIndex, p->zTerm, (int)strlen(p->zTerm),
              (pTerm->bPrefix ? FTS5INDEX_QUERY_PREFIX : 0) |
              (pExpr->bDesc ? FTS5INDEX_QUERY_DESC : 0),
              pNear->pColset,
              &p->pIter
          );
          assert( (rc==SQLITE_OK)==(p->pIter!=0) );
          if( rc!=SQLITE_OK ) return rc;
          if( 0==sqlite3Fts5IterEof(p->pIter) ){
            bHit = 1;
          }
        }

        if( bHit==0 ){
          pNode->bEof = 1;
          return SQLITE_OK;
        }
      }
    }
  }

  pNode->bEof = 0;
  return SQLITE_OK;
}