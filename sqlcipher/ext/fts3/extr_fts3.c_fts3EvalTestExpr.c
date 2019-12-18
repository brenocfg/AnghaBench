#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  iPrevId; int /*<<< orphan*/  pDeferred; } ;
struct TYPE_15__ {int eType; int /*<<< orphan*/  iDocid; int /*<<< orphan*/  bEof; int /*<<< orphan*/  bDeferred; TYPE_3__* pPhrase; struct TYPE_15__* pRight; struct TYPE_15__* pLeft; TYPE_1__* pParent; } ;
struct TYPE_13__ {int /*<<< orphan*/  pList; int /*<<< orphan*/  bFreeList; } ;
struct TYPE_14__ {TYPE_2__ doclist; } ;
struct TYPE_12__ {int const eType; } ;
typedef  TYPE_3__ Fts3Phrase ;
typedef  TYPE_4__ Fts3Expr ;
typedef  TYPE_5__ Fts3Cursor ;

/* Variables and functions */
#define  FTSQUERY_AND 131 
#define  FTSQUERY_NEAR 130 
#define  FTSQUERY_NOT 129 
#define  FTSQUERY_OR 128 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3EvalDeferredPhrase (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  fts3EvalInvalidatePoslist (TYPE_3__*) ; 
 int /*<<< orphan*/  fts3EvalNearTest (TYPE_4__*,int*) ; 

__attribute__((used)) static int fts3EvalTestExpr(
  Fts3Cursor *pCsr,               /* FTS cursor handle */
  Fts3Expr *pExpr,                /* Expr to test. May or may not be root. */
  int *pRc                        /* IN/OUT: Error code */
){
  int bHit = 1;                   /* Return value */
  if( *pRc==SQLITE_OK ){
    switch( pExpr->eType ){
      case FTSQUERY_NEAR:
      case FTSQUERY_AND:
        bHit = (
            fts3EvalTestExpr(pCsr, pExpr->pLeft, pRc)
         && fts3EvalTestExpr(pCsr, pExpr->pRight, pRc)
         && fts3EvalNearTest(pExpr, pRc)
        );

        /* If the NEAR expression does not match any rows, zero the doclist for 
        ** all phrases involved in the NEAR. This is because the snippet(),
        ** offsets() and matchinfo() functions are not supposed to recognize 
        ** any instances of phrases that are part of unmatched NEAR queries. 
        ** For example if this expression:
        **
        **    ... MATCH 'a OR (b NEAR c)'
        **
        ** is matched against a row containing:
        **
        **        'a b d e'
        **
        ** then any snippet() should ony highlight the "a" term, not the "b"
        ** (as "b" is part of a non-matching NEAR clause).
        */
        if( bHit==0 
         && pExpr->eType==FTSQUERY_NEAR 
         && (pExpr->pParent==0 || pExpr->pParent->eType!=FTSQUERY_NEAR)
        ){
          Fts3Expr *p;
          for(p=pExpr; p->pPhrase==0; p=p->pLeft){
            if( p->pRight->iDocid==pCsr->iPrevId ){
              fts3EvalInvalidatePoslist(p->pRight->pPhrase);
            }
          }
          if( p->iDocid==pCsr->iPrevId ){
            fts3EvalInvalidatePoslist(p->pPhrase);
          }
        }

        break;

      case FTSQUERY_OR: {
        int bHit1 = fts3EvalTestExpr(pCsr, pExpr->pLeft, pRc);
        int bHit2 = fts3EvalTestExpr(pCsr, pExpr->pRight, pRc);
        bHit = bHit1 || bHit2;
        break;
      }

      case FTSQUERY_NOT:
        bHit = (
            fts3EvalTestExpr(pCsr, pExpr->pLeft, pRc)
         && !fts3EvalTestExpr(pCsr, pExpr->pRight, pRc)
        );
        break;

      default: {
#ifndef SQLITE_DISABLE_FTS4_DEFERRED
        if( pCsr->pDeferred 
         && (pExpr->iDocid==pCsr->iPrevId || pExpr->bDeferred)
        ){
          Fts3Phrase *pPhrase = pExpr->pPhrase;
          assert( pExpr->bDeferred || pPhrase->doclist.bFreeList==0 );
          if( pExpr->bDeferred ){
            fts3EvalInvalidatePoslist(pPhrase);
          }
          *pRc = fts3EvalDeferredPhrase(pCsr, pPhrase);
          bHit = (pPhrase->doclist.pList!=0);
          pExpr->iDocid = pCsr->iPrevId;
        }else
#endif
        {
          bHit = (pExpr->bEof==0 && pExpr->iDocid==pCsr->iPrevId);
        }
        break;
      }
    }
  }
  return bHit;
}