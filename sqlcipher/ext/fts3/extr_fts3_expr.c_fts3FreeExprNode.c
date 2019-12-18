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
struct TYPE_4__ {scalar_t__ eType; scalar_t__ pPhrase; struct TYPE_4__* aMI; } ;
typedef  TYPE_1__ Fts3Expr ;

/* Variables and functions */
 scalar_t__ FTSQUERY_PHRASE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3Fts3EvalPhraseCleanup (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static void fts3FreeExprNode(Fts3Expr *p){
  assert( p->eType==FTSQUERY_PHRASE || p->pPhrase==0 );
  sqlite3Fts3EvalPhraseCleanup(p->pPhrase);
  sqlite3_free(p->aMI);
  sqlite3_free(p);
}