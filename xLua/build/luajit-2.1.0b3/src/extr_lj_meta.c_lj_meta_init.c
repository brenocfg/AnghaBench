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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/ * gcroot; } ;
typedef  TYPE_1__ global_State ;
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 size_t GCROOT_MMNAME ; 
 char* MMDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMNAME ; 
 int /*<<< orphan*/ * lj_str_new (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lj_meta_init(lua_State *L)
{
#define MMNAME(name)	"__" #name
  const char *metanames = MMDEF(MMNAME);
#undef MMNAME
  global_State *g = G(L);
  const char *p, *q;
  uint32_t mm;
  for (mm = 0, p = metanames; *p; mm++, p = q) {
    GCstr *s;
    for (q = p+2; *q && *q != '_'; q++) ;
    s = lj_str_new(L, p, (size_t)(q-p));
    /* NOBARRIER: g->gcroot[] is a GC root. */
    setgcref(g->gcroot[GCROOT_MMNAME+mm], obj2gco(s));
  }
}