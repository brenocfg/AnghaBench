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
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_5__ {int /*<<< orphan*/  ctypeid; } ;
struct TYPE_4__ {int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  MMS ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 int /*<<< orphan*/  G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LJ_ERR_FFI_BADMM ; 
 int /*<<< orphan*/  ctype_cid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ctype_cts (int /*<<< orphan*/ *) ; 
 scalar_t__ ctype_isptr (int /*<<< orphan*/ ) ; 
 TYPE_1__* ctype_raw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ffi_checkcdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lj_ctype_meta (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ctype_repr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_err_callerv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lj_meta_tailcall (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmname_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ffi_pairs(lua_State *L, MMS mm)
{
  CTState *cts = ctype_cts(L);
  CTypeID id = ffi_checkcdata(L, 1)->ctypeid;
  CType *ct = ctype_raw(cts, id);
  cTValue *tv;
  if (ctype_isptr(ct->info)) id = ctype_cid(ct->info);
  tv = lj_ctype_meta(cts, id, mm);
  if (!tv)
    lj_err_callerv(L, LJ_ERR_FFI_BADMM, strdata(lj_ctype_repr(L, id, NULL)),
		   strdata(mmname_str(G(L), mm)));
  return lj_meta_tailcall(L, tv);
}