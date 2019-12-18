#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_int64 ;
struct TYPE_10__ {scalar_t__ eType; int nNear; TYPE_3__* pPhrase; TYPE_2__* pRight; struct TYPE_10__* pParent; struct TYPE_10__* pLeft; } ;
struct TYPE_7__ {scalar_t__ nList; char* pList; } ;
struct TYPE_9__ {int nToken; TYPE_1__ doclist; } ;
struct TYPE_8__ {TYPE_3__* pPhrase; } ;
typedef  TYPE_3__ Fts3Phrase ;
typedef  TYPE_4__ Fts3Expr ;

/* Variables and functions */
 scalar_t__ FTSQUERY_NEAR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3EvalNearTrim (int,char*,char**,int*,TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc64 (int) ; 

__attribute__((used)) static int fts3EvalNearTest(Fts3Expr *pExpr, int *pRc){
  int res = 1;

  /* The following block runs if pExpr is the root of a NEAR query.
  ** For example, the query:
  **
  **         "w" NEAR "x" NEAR "y" NEAR "z"
  **
  ** which is represented in tree form as:
  **
  **                               |
  **                          +--NEAR--+      <-- root of NEAR query
  **                          |        |
  **                     +--NEAR--+   "z"
  **                     |        |
  **                +--NEAR--+   "y"
  **                |        |
  **               "w"      "x"
  **
  ** The right-hand child of a NEAR node is always a phrase. The 
  ** left-hand child may be either a phrase or a NEAR node. There are
  ** no exceptions to this - it's the way the parser in fts3_expr.c works.
  */
  if( *pRc==SQLITE_OK 
   && pExpr->eType==FTSQUERY_NEAR 
   && (pExpr->pParent==0 || pExpr->pParent->eType!=FTSQUERY_NEAR)
  ){
    Fts3Expr *p; 
    sqlite3_int64 nTmp = 0;       /* Bytes of temp space */
    char *aTmp;                   /* Temp space for PoslistNearMerge() */

    /* Allocate temporary working space. */
    for(p=pExpr; p->pLeft; p=p->pLeft){
      assert( p->pRight->pPhrase->doclist.nList>0 );
      nTmp += p->pRight->pPhrase->doclist.nList;
    }
    nTmp += p->pPhrase->doclist.nList;
    aTmp = sqlite3_malloc64(nTmp*2);
    if( !aTmp ){
      *pRc = SQLITE_NOMEM;
      res = 0;
    }else{
      char *aPoslist = p->pPhrase->doclist.pList;
      int nToken = p->pPhrase->nToken;

      for(p=p->pParent;res && p && p->eType==FTSQUERY_NEAR; p=p->pParent){
        Fts3Phrase *pPhrase = p->pRight->pPhrase;
        int nNear = p->nNear;
        res = fts3EvalNearTrim(nNear, aTmp, &aPoslist, &nToken, pPhrase);
      }

      aPoslist = pExpr->pRight->pPhrase->doclist.pList;
      nToken = pExpr->pRight->pPhrase->nToken;
      for(p=pExpr->pLeft; p && res; p=p->pLeft){
        int nNear;
        Fts3Phrase *pPhrase;
        assert( p->pParent && p->pParent->pLeft==p );
        nNear = p->pParent->nNear;
        pPhrase = (
            p->eType==FTSQUERY_NEAR ? p->pRight->pPhrase : p->pPhrase
        );
        res = fts3EvalNearTrim(nNear, aTmp, &aPoslist, &nToken, pPhrase);
      }
    }

    sqlite3_free(aTmp);
  }

  return res;
}