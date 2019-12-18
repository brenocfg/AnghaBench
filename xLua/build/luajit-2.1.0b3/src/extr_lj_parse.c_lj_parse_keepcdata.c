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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {TYPE_1__* fs; int /*<<< orphan*/ * L; } ;
struct TYPE_4__ {int /*<<< orphan*/  kt; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_2__ LexState ;
typedef  int /*<<< orphan*/  GCcdata ;

/* Variables and functions */
 int /*<<< orphan*/  lj_tab_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setboolV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setcdataV (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void lj_parse_keepcdata(LexState *ls, TValue *tv, GCcdata *cd)
{
  /* NOBARRIER: the key is new or kept alive. */
  lua_State *L = ls->L;
  setcdataV(L, tv, cd);
  setboolV(lj_tab_set(L, ls->fs->kt, tv), 1);
}