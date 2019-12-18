#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_4__ {int /*<<< orphan*/  metatable; } ;
struct TYPE_3__ {int /*<<< orphan*/  metatable; } ;
typedef  int /*<<< orphan*/  MMS ;
typedef  int /*<<< orphan*/  GCtab ;

/* Variables and functions */
 int /*<<< orphan*/  G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  basemt_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_tab_getstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmname_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * niltv (int /*<<< orphan*/ *) ; 
 TYPE_2__* tabV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tabref (int /*<<< orphan*/ ) ; 
 scalar_t__ tvistab (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisudata (int /*<<< orphan*/ *) ; 
 TYPE_1__* udataV (int /*<<< orphan*/ *) ; 

cTValue *lj_meta_lookup(lua_State *L, cTValue *o, MMS mm)
{
  GCtab *mt;
  if (tvistab(o))
    mt = tabref(tabV(o)->metatable);
  else if (tvisudata(o))
    mt = tabref(udataV(o)->metatable);
  else
    mt = tabref(basemt_obj(G(L), o));
  if (mt) {
    cTValue *mo = lj_tab_getstr(mt, mmname_str(G(L), mm));
    if (mo)
      return mo;
  }
  return niltv(L);
}