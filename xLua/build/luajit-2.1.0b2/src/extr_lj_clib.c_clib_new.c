#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_14__ {int /*<<< orphan*/ * cache; } ;
struct TYPE_13__ {int /*<<< orphan*/  metatable; int /*<<< orphan*/  udtype; } ;
typedef  TYPE_2__ GCudata ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  TYPE_3__ CLibrary ;

/* Variables and functions */
 int /*<<< orphan*/  UDTYPE_FFI_CLIB ; 
 int /*<<< orphan*/ * lj_tab_new (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* lj_udata_new (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setudataV (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ uddata (TYPE_2__*) ; 

__attribute__((used)) static CLibrary *clib_new(lua_State *L, GCtab *mt)
{
  GCtab *t = lj_tab_new(L, 0, 0);
  GCudata *ud = lj_udata_new(L, sizeof(CLibrary), t);
  CLibrary *cl = (CLibrary *)uddata(ud);
  cl->cache = t;
  ud->udtype = UDTYPE_FFI_CLIB;
  /* NOBARRIER: The GCudata is new (marked white). */
  setgcref(ud->metatable, obj2gco(mt));
  setudataV(L, L->top++, ud);
  return cl;
}