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
struct TYPE_4__ {int nPhrase; struct TYPE_4__* pColset; int /*<<< orphan*/ * apPhrase; } ;
typedef  TYPE_1__ Fts5ExprNearset ;

/* Variables and functions */
 int /*<<< orphan*/  fts5ExprPhraseFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

void sqlite3Fts5ParseNearsetFree(Fts5ExprNearset *pNear){
  if( pNear ){
    int i;
    for(i=0; i<pNear->nPhrase; i++){
      fts5ExprPhraseFree(pNear->apPhrase[i]);
    }
    sqlite3_free(pNear->pColset);
    sqlite3_free(pNear);
  }
}