#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_9__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * top; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_11__ {int /*<<< orphan*/  ctypeid; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  MMS ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  int /*<<< orphan*/  CType ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_FFI_BADIDXW ; 
 int /*<<< orphan*/  LJ_ERR_FFI_BADMEMBER ; 
 int /*<<< orphan*/ * LJ_FR2 ; 
 int /*<<< orphan*/  MM_index ; 
 TYPE_9__* cdataV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copyTV (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctype_typeid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_ctype_meta (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ctype_repr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_err_callerv (TYPE_1__*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int lj_meta_tailcall (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_meta_tget (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_meta_tset (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* lj_typename (int /*<<< orphan*/ *) ; 
 char const* strVdata (int /*<<< orphan*/ *) ; 
 char* strdata (int /*<<< orphan*/ ) ; 
 scalar_t__ tviscdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisfunc (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ffi_index_meta(lua_State *L, CTState *cts, CType *ct, MMS mm)
{
  CTypeID id = ctype_typeid(cts, ct);
  cTValue *tv = lj_ctype_meta(cts, id, mm);
  TValue *base = L->base;
  if (!tv) {
    const char *s;
  err_index:
    s = strdata(lj_ctype_repr(L, id, NULL));
    if (tvisstr(L->base+1)) {
      lj_err_callerv(L, LJ_ERR_FFI_BADMEMBER, s, strVdata(L->base+1));
    } else {
      const char *key = tviscdata(L->base+1) ?
	strdata(lj_ctype_repr(L, cdataV(L->base+1)->ctypeid, NULL)) :
	lj_typename(L->base+1);
      lj_err_callerv(L, LJ_ERR_FFI_BADIDXW, s, key);
    }
  }
  if (!tvisfunc(tv)) {
    if (mm == MM_index) {
      cTValue *o = lj_meta_tget(L, tv, base+1);
      if (o) {
	if (tvisnil(o)) goto err_index;
	copyTV(L, L->top-1, o);
	return 1;
      }
    } else {
      TValue *o = lj_meta_tset(L, tv, base+1);
      if (o) {
	copyTV(L, o, base+2);
	return 0;
      }
    }
    copyTV(L, base, L->top);
    tv = L->top-1-LJ_FR2;
  }
  return lj_meta_tailcall(L, tv);
}