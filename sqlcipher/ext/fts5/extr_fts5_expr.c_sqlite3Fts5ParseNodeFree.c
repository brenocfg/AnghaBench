#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nChild; int /*<<< orphan*/  pNear; struct TYPE_4__** apChild; } ;
typedef  TYPE_1__ Fts5ExprNode ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3Fts5ParseNearsetFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

void sqlite3Fts5ParseNodeFree(Fts5ExprNode *p){
  if( p ){
    int i;
    for(i=0; i<p->nChild; i++){
      sqlite3Fts5ParseNodeFree(p->apChild[i]);
    }
    sqlite3Fts5ParseNearsetFree(p->pNear);
    sqlite3_free(p);
  }
}