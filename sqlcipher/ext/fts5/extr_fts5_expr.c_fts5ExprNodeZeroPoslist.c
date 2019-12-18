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
struct TYPE_8__ {scalar_t__ eType; int nChild; struct TYPE_8__** apChild; TYPE_4__* pNear; } ;
struct TYPE_6__ {scalar_t__ n; } ;
struct TYPE_7__ {TYPE_1__ poslist; } ;
typedef  TYPE_2__ Fts5ExprPhrase ;
typedef  TYPE_3__ Fts5ExprNode ;
typedef  TYPE_4__ Fts5ExprNearset ;

/* Variables and functions */
 scalar_t__ FTS5_STRING ; 
 scalar_t__ FTS5_TERM ; 

__attribute__((used)) static void fts5ExprNodeZeroPoslist(Fts5ExprNode *pNode){
  if( pNode->eType==FTS5_STRING || pNode->eType==FTS5_TERM ){
    Fts5ExprNearset *pNear = pNode->pNear;
    int i;
    for(i=0; i<pNear->nPhrase; i++){
      Fts5ExprPhrase *pPhrase = pNear->apPhrase[i];
      pPhrase->poslist.n = 0;
    }
  }else{
    int i;
    for(i=0; i<pNode->nChild; i++){
      fts5ExprNodeZeroPoslist(pNode->apChild[i]);
    }
  }
}