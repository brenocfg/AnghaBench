#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_25__ {void (* func ) () ;scalar_t__ spadj; } ;
struct TYPE_21__ {unsigned int slot; } ;
struct TYPE_24__ {scalar_t__ tab; int /*<<< orphan*/  miscmap; TYPE_1__ cb; } ;
struct TYPE_23__ {int /*<<< orphan*/  info; int /*<<< orphan*/  size; } ;
struct TYPE_22__ {int /*<<< orphan*/  ctypeid; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_2__ GCcdata ;
typedef  TYPE_3__ CType ;
typedef  TYPE_4__ CTState ;
typedef  int /*<<< orphan*/  CTSize ;
typedef  TYPE_5__ CCallState ;

/* Variables and functions */
 int /*<<< orphan*/  CCONV ; 
 scalar_t__ CTCC_CDECL ; 
 int /*<<< orphan*/  CTCC_STDCALL ; 
 int /*<<< orphan*/  CTF_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTSIZE_PTR ; 
 int /*<<< orphan*/  G (int /*<<< orphan*/ *) ; 
 scalar_t__ ccall_get_results (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*,TYPE_5__*,int*) ; 
 int ccall_set_args (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*,TYPE_5__*) ; 
 scalar_t__ cdata_getptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdataptr (TYPE_2__*) ; 
 scalar_t__ ctype_cconv (int /*<<< orphan*/ ) ; 
 TYPE_4__* ctype_cts (int /*<<< orphan*/ *) ; 
 scalar_t__ ctype_isfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isptr (int /*<<< orphan*/ ) ; 
 TYPE_3__* ctype_raw (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ctype_rawchild (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  lj_gc_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_tab_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_trace_abort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_vm_ffi_call (TYPE_5__*) ; 
 int /*<<< orphan*/  setboolV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setlightudV (int /*<<< orphan*/ *,void*) ; 

int lj_ccall_func(lua_State *L, GCcdata *cd)
{
  CTState *cts = ctype_cts(L);
  CType *ct = ctype_raw(cts, cd->ctypeid);
  CTSize sz = CTSIZE_PTR;
  if (ctype_isptr(ct->info)) {
    sz = ct->size;
    ct = ctype_rawchild(cts, ct);
  }
  if (ctype_isfunc(ct->info)) {
    CCallState cc;
    int gcsteps, ret;
    cc.func = (void (*)(void))cdata_getptr(cdataptr(cd), sz);
    gcsteps = ccall_set_args(L, cts, ct, &cc);
    ct = (CType *)((intptr_t)ct-(intptr_t)cts->tab);
    cts->cb.slot = ~0u;
    lj_vm_ffi_call(&cc);
    if (cts->cb.slot != ~0u) {  /* Blacklist function that called a callback. */
      TValue tv;
      setlightudV(&tv, (void *)cc.func);
      setboolV(lj_tab_set(L, cts->miscmap, &tv), 1);
    }
    ct = (CType *)((intptr_t)ct+(intptr_t)cts->tab);  /* May be reallocated. */
    gcsteps += ccall_get_results(L, cts, ct, &cc, &ret);
#if LJ_TARGET_X86 && LJ_ABI_WIN
    /* Automatically detect __stdcall and fix up C function declaration. */
    if (cc.spadj && ctype_cconv(ct->info) == CTCC_CDECL) {
      CTF_INSERT(ct->info, CCONV, CTCC_STDCALL);
      lj_trace_abort(G(L));
    }
#endif
    while (gcsteps-- > 0)
      lj_gc_check(L);
    return ret;
  }
  return -1;  /* Not a function. */
}