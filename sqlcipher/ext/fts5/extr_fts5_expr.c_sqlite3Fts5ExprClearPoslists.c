#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ n; } ;
struct TYPE_15__ {int nPhrase; TYPE_2__* pRoot; TYPE_1__** apExprPhrase; } ;
struct TYPE_14__ {scalar_t__ iRowid; scalar_t__ bEof; } ;
struct TYPE_13__ {int bMiss; } ;
struct TYPE_12__ {scalar_t__ iRowid; } ;
struct TYPE_11__ {int nTerm; TYPE_4__* pNode; TYPE_6__ poslist; } ;
typedef  TYPE_3__ Fts5PoslistPopulator ;
typedef  TYPE_4__ Fts5ExprNode ;
typedef  TYPE_5__ Fts5Expr ;
typedef  TYPE_6__ Fts5Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* sqlite3_malloc64 (int) ; 

Fts5PoslistPopulator *sqlite3Fts5ExprClearPoslists(Fts5Expr *pExpr, int bLive){
  Fts5PoslistPopulator *pRet;
  pRet = sqlite3_malloc64(sizeof(Fts5PoslistPopulator)*pExpr->nPhrase);
  if( pRet ){
    int i;
    memset(pRet, 0, sizeof(Fts5PoslistPopulator)*pExpr->nPhrase);
    for(i=0; i<pExpr->nPhrase; i++){
      Fts5Buffer *pBuf = &pExpr->apExprPhrase[i]->poslist;
      Fts5ExprNode *pNode = pExpr->apExprPhrase[i]->pNode;
      assert( pExpr->apExprPhrase[i]->nTerm==1 );
      if( bLive && 
          (pBuf->n==0 || pNode->iRowid!=pExpr->pRoot->iRowid || pNode->bEof)
      ){
        pRet[i].bMiss = 1;
      }else{
        pBuf->n = 0;
      }
    }
  }
  return pRet;
}