#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nPhrase; TYPE_2__** apPhrase; } ;
struct TYPE_8__ {int eType; int /*<<< orphan*/  xNext; TYPE_4__* pNear; } ;
struct TYPE_7__ {int nTerm; TYPE_1__* aTerm; } ;
struct TYPE_6__ {int /*<<< orphan*/  bFirst; int /*<<< orphan*/  pSynonym; } ;
typedef  TYPE_3__ Fts5ExprNode ;
typedef  TYPE_4__ Fts5ExprNearset ;

/* Variables and functions */
#define  FTS5_AND 130 
 int FTS5_NOT ; 
#define  FTS5_OR 129 
#define  FTS5_STRING 128 
 int FTS5_TERM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5ExprNodeNext_AND ; 
 int /*<<< orphan*/  fts5ExprNodeNext_NOT ; 
 int /*<<< orphan*/  fts5ExprNodeNext_OR ; 
 int /*<<< orphan*/  fts5ExprNodeNext_STRING ; 
 int /*<<< orphan*/  fts5ExprNodeNext_TERM ; 

__attribute__((used)) static void fts5ExprAssignXNext(Fts5ExprNode *pNode){
  switch( pNode->eType ){
    case FTS5_STRING: {
      Fts5ExprNearset *pNear = pNode->pNear;
      if( pNear->nPhrase==1 && pNear->apPhrase[0]->nTerm==1 
       && pNear->apPhrase[0]->aTerm[0].pSynonym==0
       && pNear->apPhrase[0]->aTerm[0].bFirst==0
      ){
        pNode->eType = FTS5_TERM;
        pNode->xNext = fts5ExprNodeNext_TERM;
      }else{
        pNode->xNext = fts5ExprNodeNext_STRING;
      }
      break;
    };

    case FTS5_OR: {
      pNode->xNext = fts5ExprNodeNext_OR;
      break;
    };

    case FTS5_AND: {
      pNode->xNext = fts5ExprNodeNext_AND;
      break;
    };

    default: assert( pNode->eType==FTS5_NOT ); {
      pNode->xNext = fts5ExprNodeNext_NOT;
      break;
    };
  }
}