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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  codesize; int /*<<< orphan*/ * code; } ;
typedef  TYPE_1__ Pattern ;

/* Variables and functions */
 TYPE_1__* getpattern (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prepcompile (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  printktable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printpatt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp_printcode (lua_State *L) {
  Pattern *p = getpattern(L, 1);
  printktable(L, 1);
  if (p->code == NULL)  /* not compiled yet? */
    prepcompile(L, p, 1);
  printpatt(p->code, p->codesize);
  return 0;
}