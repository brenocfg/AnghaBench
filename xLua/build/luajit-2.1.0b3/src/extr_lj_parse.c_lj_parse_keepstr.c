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
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
 int /*<<< orphan*/  lj_gc_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_str_new (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/ * lj_tab_setstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setboolV (int /*<<< orphan*/ *,int) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 

GCstr *lj_parse_keepstr(LexState *ls, const char *str, size_t len)
{
  /* NOBARRIER: the key is new or kept alive. */
  lua_State *L = ls->L;
  GCstr *s = lj_str_new(L, str, len);
  TValue *tv = lj_tab_setstr(L, ls->fs->kt, s);
  if (tvisnil(tv)) setboolV(tv, 1);
  lj_gc_check(L);
  return s;
}