#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * top; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_8__ {scalar_t__ udtype; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  CLibrary ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TSTRING ; 
 int /*<<< orphan*/  LUA_TUSERDATA ; 
 scalar_t__ UDTYPE_FFI_CLIB ; 
 int /*<<< orphan*/ * lj_clib_index (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_argt (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisudata (int /*<<< orphan*/ *) ; 
 TYPE_2__* udataV (int /*<<< orphan*/ *) ; 
 scalar_t__ uddata (TYPE_2__*) ; 

__attribute__((used)) static TValue *ffi_clib_index(lua_State *L)
{
  TValue *o = L->base;
  CLibrary *cl;
  if (!(o < L->top && tvisudata(o) && udataV(o)->udtype == UDTYPE_FFI_CLIB))
    lj_err_argt(L, 1, LUA_TUSERDATA);
  cl = (CLibrary *)uddata(udataV(o));
  if (!(o+1 < L->top && tvisstr(o+1)))
    lj_err_argt(L, 2, LUA_TSTRING);
  return lj_clib_index(L, cl, strV(o+1));
}