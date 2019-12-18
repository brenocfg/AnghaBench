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
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_10__ {int eType; int nChild; struct TYPE_10__** apChild; TYPE_3__* pNear; scalar_t__ bEof; int /*<<< orphan*/  iRowid; } ;
struct TYPE_9__ {TYPE_2__** apPhrase; } ;
struct TYPE_7__ {int /*<<< orphan*/  n; } ;
struct TYPE_8__ {TYPE_1__ poslist; } ;
typedef  TYPE_4__ Fts5ExprNode ;

/* Variables and functions */
#define  FTS5_AND 131 
 int FTS5_NOT ; 
#define  FTS5_OR 130 
#define  FTS5_STRING 129 
#define  FTS5_TERM 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5ExprClearPoslists (TYPE_4__*) ; 

__attribute__((used)) static int fts5ExprCheckPoslists(Fts5ExprNode *pNode, i64 iRowid){
  pNode->iRowid = iRowid;
  pNode->bEof = 0;
  switch( pNode->eType ){
    case FTS5_TERM:
    case FTS5_STRING:
      return (pNode->pNear->apPhrase[0]->poslist.n>0);

    case FTS5_AND: {
      int i;
      for(i=0; i<pNode->nChild; i++){
        if( fts5ExprCheckPoslists(pNode->apChild[i], iRowid)==0 ){
          fts5ExprClearPoslists(pNode);
          return 0;
        }
      }
      break;
    }

    case FTS5_OR: {
      int i;
      int bRet = 0;
      for(i=0; i<pNode->nChild; i++){
        if( fts5ExprCheckPoslists(pNode->apChild[i], iRowid) ){
          bRet = 1;
        }
      }
      return bRet;
    }

    default: {
      assert( pNode->eType==FTS5_NOT );
      if( 0==fts5ExprCheckPoslists(pNode->apChild[0], iRowid)
          || 0!=fts5ExprCheckPoslists(pNode->apChild[1], iRowid)
        ){
        fts5ExprClearPoslists(pNode);
        return 0;
      }
      break;
    }
  }
  return 1;
}