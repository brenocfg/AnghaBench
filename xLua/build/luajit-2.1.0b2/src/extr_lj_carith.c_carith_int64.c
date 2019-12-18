#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_10__ {int info; int size; } ;
struct TYPE_9__ {int /*<<< orphan*/ * p; TYPE_5__** ct; } ;
typedef  int MMS ;
typedef  int /*<<< orphan*/  GCcdata ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  int /*<<< orphan*/  CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  TYPE_2__ CDArith ;

/* Variables and functions */
 int CTF_UNSIGNED ; 
 int /*<<< orphan*/  CTID_INT64 ; 
 int /*<<< orphan*/  CTID_UINT64 ; 
#define  MM_add 137 
#define  MM_div 136 
#define  MM_eq 135 
#define  MM_le 134 
#define  MM_lt 133 
#define  MM_mod 132 
#define  MM_mul 131 
#define  MM_pow 130 
#define  MM_sub 129 
#define  MM_unm 128 
 scalar_t__ cdataptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ctype_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isnum (int) ; 
 int /*<<< orphan*/  lj_carith_divi64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_carith_divu64 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lj_carith_modi64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_carith_modu64 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lj_carith_powi64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_carith_powu64 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lj_cconv_ct_ct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_cdata_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lj_gc_check (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setboolV (scalar_t__,int) ; 
 int /*<<< orphan*/  setcdataV (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int carith_int64(lua_State *L, CTState *cts, CDArith *ca, MMS mm)
{
  if (ctype_isnum(ca->ct[0]->info) && ca->ct[0]->size <= 8 &&
      ctype_isnum(ca->ct[1]->info) && ca->ct[1]->size <= 8) {
    CTypeID id = (((ca->ct[0]->info & CTF_UNSIGNED) && ca->ct[0]->size == 8) ||
		  ((ca->ct[1]->info & CTF_UNSIGNED) && ca->ct[1]->size == 8)) ?
		 CTID_UINT64 : CTID_INT64;
    CType *ct = ctype_get(cts, id);
    GCcdata *cd;
    uint64_t u0, u1, *up;
    lj_cconv_ct_ct(cts, ct, ca->ct[0], (uint8_t *)&u0, ca->p[0], 0);
    if (mm != MM_unm)
      lj_cconv_ct_ct(cts, ct, ca->ct[1], (uint8_t *)&u1, ca->p[1], 0);
    switch (mm) {
    case MM_eq:
      setboolV(L->top-1, (u0 == u1));
      return 1;
    case MM_lt:
      setboolV(L->top-1,
	       id == CTID_INT64 ? ((int64_t)u0 < (int64_t)u1) : (u0 < u1));
      return 1;
    case MM_le:
      setboolV(L->top-1,
	       id == CTID_INT64 ? ((int64_t)u0 <= (int64_t)u1) : (u0 <= u1));
      return 1;
    default: break;
    }
    cd = lj_cdata_new(cts, id, 8);
    up = (uint64_t *)cdataptr(cd);
    setcdataV(L, L->top-1, cd);
    switch (mm) {
    case MM_add: *up = u0 + u1; break;
    case MM_sub: *up = u0 - u1; break;
    case MM_mul: *up = u0 * u1; break;
    case MM_div:
      if (id == CTID_INT64)
	*up = (uint64_t)lj_carith_divi64((int64_t)u0, (int64_t)u1);
      else
	*up = lj_carith_divu64(u0, u1);
      break;
    case MM_mod:
      if (id == CTID_INT64)
	*up = (uint64_t)lj_carith_modi64((int64_t)u0, (int64_t)u1);
      else
	*up = lj_carith_modu64(u0, u1);
      break;
    case MM_pow:
      if (id == CTID_INT64)
	*up = (uint64_t)lj_carith_powi64((int64_t)u0, (int64_t)u1);
      else
	*up = lj_carith_powu64(u0, u1);
      break;
    case MM_unm: *up = (uint64_t)-(int64_t)u0; break;
    default: lua_assert(0); break;
    }
    lj_gc_check(L);
    return 1;
  }
  return 0;
}