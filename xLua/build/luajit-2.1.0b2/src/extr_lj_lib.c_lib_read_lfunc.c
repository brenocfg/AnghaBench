#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int /*<<< orphan*/  env; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  ls ;
struct TYPE_15__ {int /*<<< orphan*/  firstline; } ;
struct TYPE_14__ {char const* p; char const* pe; int c; int level; int /*<<< orphan*/ * chunkname; TYPE_1__* L; } ;
typedef  TYPE_2__ LexState ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  TYPE_3__ GCproto ;
typedef  int /*<<< orphan*/  GCfunc ;
typedef  int /*<<< orphan*/  BCLine ;

/* Variables and functions */
 int BCDUMP_F_BE ; 
 int BCDUMP_F_STRIP ; 
 int LJ_BE ; 
 TYPE_3__* lj_bcread_proto (TYPE_2__*) ; 
 int /*<<< orphan*/ * lj_func_newL_empty (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_str_new (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  lj_tab_setstr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setfuncV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tabref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const uint8_t *lib_read_lfunc(lua_State *L, const uint8_t *p, GCtab *tab)
{
  int len = *p++;
  GCstr *name = lj_str_new(L, (const char *)p, len);
  LexState ls;
  GCproto *pt;
  GCfunc *fn;
  memset(&ls, 0, sizeof(ls));
  ls.L = L;
  ls.p = (const char *)(p+len);
  ls.pe = (const char *)~(uintptr_t)0;
  ls.c = -1;
  ls.level = (BCDUMP_F_STRIP|(LJ_BE*BCDUMP_F_BE));
  ls.chunkname = name;
  pt = lj_bcread_proto(&ls);
  pt->firstline = ~(BCLine)0;
  fn = lj_func_newL_empty(L, pt, tabref(L->env));
  /* NOBARRIER: See below for common barrier. */
  setfuncV(L, lj_tab_setstr(L, tab, name), fn);
  return (const uint8_t *)ls.p;
}