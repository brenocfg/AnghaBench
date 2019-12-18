#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_11__ {size_t sizeid; scalar_t__* cbid; size_t topid; } ;
struct TYPE_14__ {TYPE_1__ cb; int /*<<< orphan*/ * miscmap; } ;
struct TYPE_13__ {int size; int /*<<< orphan*/  info; } ;
struct TYPE_12__ {int /*<<< orphan*/  ctypeid; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  size_t MSize ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  int /*<<< orphan*/  GCfunc ;
typedef  TYPE_2__ GCcdata ;
typedef  TYPE_3__ CType ;
typedef  TYPE_4__ CTState ;

/* Variables and functions */
 scalar_t__ LJ_32 ; 
 int /*<<< orphan*/  LJ_ERR_FFI_BADCBACK ; 
 scalar_t__ cdataptr (TYPE_2__*) ; 
 TYPE_4__* ctype_cts (int /*<<< orphan*/ *) ; 
 scalar_t__ ctype_isptr (int /*<<< orphan*/ ) ; 
 TYPE_3__* ctype_raw (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ffi_checkcdata (int /*<<< orphan*/ *,int) ; 
 size_t lj_ccallback_ptr2slot (TYPE_4__*,void*) ; 
 int /*<<< orphan*/  lj_err_caller (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_gc_anybarriert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_tab_setint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setfuncV (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ffi_callback_set(lua_State *L, GCfunc *fn)
{
  GCcdata *cd = ffi_checkcdata(L, 1);
  CTState *cts = ctype_cts(L);
  CType *ct = ctype_raw(cts, cd->ctypeid);
  if (ctype_isptr(ct->info) && (LJ_32 || ct->size == 8)) {
    MSize slot = lj_ccallback_ptr2slot(cts, *(void **)cdataptr(cd));
    if (slot < cts->cb.sizeid && cts->cb.cbid[slot] != 0) {
      GCtab *t = cts->miscmap;
      TValue *tv = lj_tab_setint(L, t, (int32_t)slot);
      if (fn) {
	setfuncV(L, tv, fn);
	lj_gc_anybarriert(L, t);
      } else {
	setnilV(tv);
	cts->cb.cbid[slot] = 0;
	cts->cb.topid = slot < cts->cb.topid ? slot : cts->cb.topid;
      }
      return 0;
    }
  }
  lj_err_caller(L, LJ_ERR_FFI_BADCBACK);
  return 0;
}