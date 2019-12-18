#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ eType; int nChild; TYPE_1__* pNear; struct TYPE_15__** apChild; } ;
struct TYPE_14__ {scalar_t__* apPhrase; int nPhrase; scalar_t__ rc; } ;
struct TYPE_13__ {scalar_t__* apPhrase; int nPhrase; } ;
typedef  TYPE_2__ Fts5Parse ;
typedef  int /*<<< orphan*/  Fts5ExprPhrase ;
typedef  TYPE_3__ Fts5ExprNode ;

/* Variables and functions */
 scalar_t__ FTS5_AND ; 
 scalar_t__ FTS5_EOF ; 
 scalar_t__ FTS5_STRING ; 
 scalar_t__ FTS5_TERM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 TYPE_3__* sqlite3Fts5ParseNode (TYPE_2__*,scalar_t__,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Fts5ParseNodeFree (TYPE_3__*) ; 

Fts5ExprNode *sqlite3Fts5ParseImplicitAnd(
  Fts5Parse *pParse,              /* Parse context */
  Fts5ExprNode *pLeft,            /* Left hand child expression */
  Fts5ExprNode *pRight            /* Right hand child expression */
){
  Fts5ExprNode *pRet = 0;
  Fts5ExprNode *pPrev;

  if( pParse->rc ){
    sqlite3Fts5ParseNodeFree(pLeft);
    sqlite3Fts5ParseNodeFree(pRight);
  }else{

    assert( pLeft->eType==FTS5_STRING 
        || pLeft->eType==FTS5_TERM
        || pLeft->eType==FTS5_EOF
        || pLeft->eType==FTS5_AND
    );
    assert( pRight->eType==FTS5_STRING 
        || pRight->eType==FTS5_TERM 
        || pRight->eType==FTS5_EOF 
    );

    if( pLeft->eType==FTS5_AND ){
      pPrev = pLeft->apChild[pLeft->nChild-1];
    }else{
      pPrev = pLeft;
    }
    assert( pPrev->eType==FTS5_STRING 
        || pPrev->eType==FTS5_TERM 
        || pPrev->eType==FTS5_EOF 
        );

    if( pRight->eType==FTS5_EOF ){
      assert( pParse->apPhrase[pParse->nPhrase-1]==pRight->pNear->apPhrase[0] );
      sqlite3Fts5ParseNodeFree(pRight);
      pRet = pLeft;
      pParse->nPhrase--;
    }
    else if( pPrev->eType==FTS5_EOF ){
      Fts5ExprPhrase **ap;

      if( pPrev==pLeft ){
        pRet = pRight;
      }else{
        pLeft->apChild[pLeft->nChild-1] = pRight;
        pRet = pLeft;
      }

      ap = &pParse->apPhrase[pParse->nPhrase-1-pRight->pNear->nPhrase];
      assert( ap[0]==pPrev->pNear->apPhrase[0] );
      memmove(ap, &ap[1], sizeof(Fts5ExprPhrase*)*pRight->pNear->nPhrase);
      pParse->nPhrase--;

      sqlite3Fts5ParseNodeFree(pPrev);
    }
    else{
      pRet = sqlite3Fts5ParseNode(pParse, FTS5_AND, pLeft, pRight, 0);
    }
  }

  return pRet;
}