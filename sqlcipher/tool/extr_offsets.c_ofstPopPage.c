#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t nStack; int /*<<< orphan*/ * aStack; int /*<<< orphan*/  aPage; int /*<<< orphan*/ * aPgno; int /*<<< orphan*/  pgno; } ;
typedef  TYPE_1__ GState ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ofstPopPage(GState *p){
  if( p->nStack<=0 ) return;
  p->nStack--;
  sqlite3_free(p->aStack[p->nStack]);
  p->pgno = p->aPgno[p->nStack-1];
  p->aPage = p->aStack[p->nStack-1];
}