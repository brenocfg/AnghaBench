#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ eType; int nChild; struct TYPE_7__** apChild; } ;
typedef  TYPE_1__ Fts5ExprNode ;

/* Variables and functions */
 scalar_t__ FTS5_NOT ; 
 int /*<<< orphan*/  memcpy (TYPE_1__**,TYPE_1__**,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static void fts5ExprAddChildren(Fts5ExprNode *p, Fts5ExprNode *pSub){
  if( p->eType!=FTS5_NOT && pSub->eType==p->eType ){
    int nByte = sizeof(Fts5ExprNode*) * pSub->nChild;
    memcpy(&p->apChild[p->nChild], pSub->apChild, nByte);
    p->nChild += pSub->nChild;
    sqlite3_free(pSub);
  }else{
    p->apChild[p->nChild++] = pSub;
  }
}