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
struct TYPE_9__ {scalar_t__ eType; int nChild; struct TYPE_9__** apChild; TYPE_3__* pNear; } ;
struct TYPE_8__ {TYPE_2__** apPhrase; } ;
struct TYPE_6__ {scalar_t__ n; } ;
struct TYPE_7__ {TYPE_1__ poslist; } ;
typedef  TYPE_4__ Fts5ExprNode ;

/* Variables and functions */
 scalar_t__ FTS5_STRING ; 
 scalar_t__ FTS5_TERM ; 

__attribute__((used)) static void fts5ExprClearPoslists(Fts5ExprNode *pNode){
  if( pNode->eType==FTS5_TERM || pNode->eType==FTS5_STRING ){
    pNode->pNear->apPhrase[0]->poslist.n = 0;
  }else{
    int i;
    for(i=0; i<pNode->nChild; i++){
      fts5ExprClearPoslists(pNode->apChild[i]);
    }
  }
}