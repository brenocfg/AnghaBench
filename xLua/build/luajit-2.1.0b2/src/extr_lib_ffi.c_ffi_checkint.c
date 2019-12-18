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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * top; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 int /*<<< orphan*/  CCF_ARG (int) ; 
 int /*<<< orphan*/  CTID_INT32 ; 
 int /*<<< orphan*/  LJ_ERR_NOVAL ; 
 int /*<<< orphan*/ * ctype_cts (TYPE_1__*) ; 
 int /*<<< orphan*/  ctype_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_cconv_ct_tv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_arg (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t ffi_checkint(lua_State *L, int narg)
{
  CTState *cts = ctype_cts(L);
  TValue *o = L->base + narg-1;
  int32_t i;
  if (o >= L->top)
    lj_err_arg(L, narg, LJ_ERR_NOVAL);
  lj_cconv_ct_tv(cts, ctype_get(cts, CTID_INT32), (uint8_t *)&i, o,
		 CCF_ARG(narg));
  return i;
}