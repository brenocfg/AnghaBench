#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_15__ {int /*<<< orphan*/ * top; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_16__ {int info; int size; } ;
struct TYPE_14__ {int /*<<< orphan*/  ctypeid; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_2__ CType ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 int /*<<< orphan*/  CCF_ARG (int) ; 
 int CTF_BOOL ; 
 int CTF_FP ; 
 int CTF_UNSIGNED ; 
 int /*<<< orphan*/  CTID_INT64 ; 
 int /*<<< orphan*/  CTID_UINT64 ; 
 int CTINFO (int /*<<< orphan*/ ,int) ; 
 int CTMASK_NUM ; 
 int /*<<< orphan*/  CT_NUM ; 
 scalar_t__ LJ_DUALNUM ; 
 scalar_t__ LJ_LIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_TNUMBER ; 
 TYPE_12__* cdataV (int /*<<< orphan*/ *) ; 
 scalar_t__ cdataptr (TYPE_12__*) ; 
 TYPE_2__* ctype_child (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ctype_cid (int) ; 
 int /*<<< orphan*/ * ctype_cts (TYPE_1__*) ; 
 TYPE_2__* ctype_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isenum (int) ; 
 scalar_t__ ctype_isref (int) ; 
 TYPE_2__* ctype_raw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_cconv_ct_ct (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_argt (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_num2bit (int /*<<< orphan*/ ) ; 
 scalar_t__ lj_strscan_number (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  numV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setintV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strV (int /*<<< orphan*/ *) ; 
 scalar_t__ tviscdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisnumber (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 

uint64_t lj_carith_check64(lua_State *L, int narg, CTypeID *id)
{
  TValue *o = L->base + narg-1;
  if (o >= L->top) {
  err:
    lj_err_argt(L, narg, LUA_TNUMBER);
  } else if (LJ_LIKELY(tvisnumber(o))) {
    /* Handled below. */
  } else if (tviscdata(o)) {
    CTState *cts = ctype_cts(L);
    uint8_t *sp = (uint8_t *)cdataptr(cdataV(o));
    CTypeID sid = cdataV(o)->ctypeid;
    CType *s = ctype_get(cts, sid);
    uint64_t x;
    if (ctype_isref(s->info)) {
      sp = *(void **)sp;
      sid = ctype_cid(s->info);
    }
    s = ctype_raw(cts, sid);
    if (ctype_isenum(s->info)) s = ctype_child(cts, s);
    if ((s->info & (CTMASK_NUM|CTF_BOOL|CTF_FP|CTF_UNSIGNED)) ==
	CTINFO(CT_NUM, CTF_UNSIGNED) && s->size == 8)
      *id = CTID_UINT64;  /* Use uint64_t, since it has the highest rank. */
    else if (!*id)
      *id = CTID_INT64;  /* Use int64_t, unless already set. */
    lj_cconv_ct_ct(cts, ctype_get(cts, *id), s,
		   (uint8_t *)&x, sp, CCF_ARG(narg));
    return x;
  } else if (!(tvisstr(o) && lj_strscan_number(strV(o), o))) {
    goto err;
  }
  if (LJ_LIKELY(tvisint(o))) {
    return (uint32_t)intV(o);
  } else {
    int32_t i = lj_num2bit(numV(o));
    if (LJ_DUALNUM) setintV(o, i);
    return (uint32_t)i;
  }
}