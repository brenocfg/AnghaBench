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
struct TYPE_7__ {int /*<<< orphan*/ * top; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
 scalar_t__ LJ_LIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MM_tostring ; 
 int /*<<< orphan*/  copyTV (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_meta_lookup (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_strfmt_obj (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  lua_call (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/ * strV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisstr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GCstr *string_fmt_tostring(lua_State *L, int arg, int retry)
{
  TValue *o = L->base+arg-1;
  cTValue *mo;
  lua_assert(o < L->top);  /* Caller already checks for existence. */
  if (LJ_LIKELY(tvisstr(o)))
    return strV(o);
  if (retry != 2 && !tvisnil(mo = lj_meta_lookup(L, o, MM_tostring))) {
    copyTV(L, L->top++, mo);
    copyTV(L, L->top++, o);
    lua_call(L, 1, 1);
    copyTV(L, L->base+arg-1, --L->top);
    return NULL;  /* Buffer may be overwritten, retry. */
  }
  return lj_strfmt_obj(L, o);
}