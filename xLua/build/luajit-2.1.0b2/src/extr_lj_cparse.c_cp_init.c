#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int linenumber; int* packstack; int /*<<< orphan*/  tmask; scalar_t__ tok; int /*<<< orphan*/ * p; int /*<<< orphan*/  sb; int /*<<< orphan*/  L; scalar_t__ curpack; scalar_t__ depth; } ;
typedef  TYPE_1__ CPState ;

/* Variables and functions */
 int /*<<< orphan*/  CPNS_DEFAULT ; 
 int /*<<< orphan*/  cp_get (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_next (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_buf_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cp_init(CPState *cp)
{
  cp->linenumber = 1;
  cp->depth = 0;
  cp->curpack = 0;
  cp->packstack[0] = 255;
  lj_buf_init(cp->L, &cp->sb);
  lua_assert(cp->p != NULL);
  cp_get(cp);  /* Read-ahead first char. */
  cp->tok = 0;
  cp->tmask = CPNS_DEFAULT;
  cp_next(cp);  /* Read-ahead first token. */
}