#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pNC; } ;
struct TYPE_5__ {TYPE_1__ u; int /*<<< orphan*/ * pParse; scalar_t__ xSelectCallback2; int /*<<< orphan*/  xSelectCallback; int /*<<< orphan*/  xExprCallback; } ;
typedef  TYPE_2__ Walker ;
typedef  int /*<<< orphan*/  Select ;
typedef  int /*<<< orphan*/  Parse ;
typedef  int /*<<< orphan*/  NameContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  resolveExprStep ; 
 int /*<<< orphan*/  resolveSelectStep ; 
 int /*<<< orphan*/  sqlite3WalkSelect (TYPE_2__*,int /*<<< orphan*/ *) ; 

void sqlite3ResolveSelectNames(
  Parse *pParse,         /* The parser context */
  Select *p,             /* The SELECT statement being coded. */
  NameContext *pOuterNC  /* Name context for parent SELECT statement */
){
  Walker w;

  assert( p!=0 );
  w.xExprCallback = resolveExprStep;
  w.xSelectCallback = resolveSelectStep;
  w.xSelectCallback2 = 0;
  w.pParse = pParse;
  w.u.pNC = pOuterNC;
  sqlite3WalkSelect(&w, p);
}