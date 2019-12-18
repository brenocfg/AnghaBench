#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  intptr_t ptrdiff_t ;
struct TYPE_11__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  intptr_t int32_t ;
struct TYPE_13__ {int /*<<< orphan*/ ** p; TYPE_2__** ct; } ;
struct TYPE_12__ {int /*<<< orphan*/  info; } ;
typedef  scalar_t__ MMS ;
typedef  int /*<<< orphan*/  GCcdata ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_2__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  scalar_t__ CTSize ;
typedef  TYPE_3__ CDArith ;

/* Variables and functions */
 int /*<<< orphan*/  CCF_IGNQUAL ; 
 int CTALIGN_PTR ; 
 int /*<<< orphan*/  CTID_INT_PSZ ; 
 int /*<<< orphan*/  CTINFO (int /*<<< orphan*/ ,int) ; 
 scalar_t__ CTSIZE_INVALID ; 
 int /*<<< orphan*/  CTSIZE_PTR ; 
 int /*<<< orphan*/  CT_PTR ; 
 scalar_t__ MM_add ; 
 scalar_t__ MM_eq ; 
 scalar_t__ MM_le ; 
 scalar_t__ MM_lt ; 
 scalar_t__ MM_sub ; 
 scalar_t__ cdataptr (int /*<<< orphan*/ *) ; 
 int ctype_cid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isnum (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isptr (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isrefarray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_cconv_compatptr (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_cconv_ct_ct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_cdata_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ctype_intern (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_ctype_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lj_gc_check (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setboolV (scalar_t__,int) ; 
 int /*<<< orphan*/  setcdataV (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setintptrV (scalar_t__,intptr_t) ; 

__attribute__((used)) static int carith_ptr(lua_State *L, CTState *cts, CDArith *ca, MMS mm)
{
  CType *ctp = ca->ct[0];
  uint8_t *pp = ca->p[0];
  ptrdiff_t idx;
  CTSize sz;
  CTypeID id;
  GCcdata *cd;
  if (ctype_isptr(ctp->info) || ctype_isrefarray(ctp->info)) {
    if ((mm == MM_sub || mm == MM_eq || mm == MM_lt || mm == MM_le) &&
	(ctype_isptr(ca->ct[1]->info) || ctype_isrefarray(ca->ct[1]->info))) {
      uint8_t *pp2 = ca->p[1];
      if (mm == MM_eq) {  /* Pointer equality. Incompatible pointers are ok. */
	setboolV(L->top-1, (pp == pp2));
	return 1;
      }
      if (!lj_cconv_compatptr(cts, ctp, ca->ct[1], CCF_IGNQUAL))
	return 0;
      if (mm == MM_sub) {  /* Pointer difference. */
	intptr_t diff;
	sz = lj_ctype_size(cts, ctype_cid(ctp->info));  /* Element size. */
	if (sz == 0 || sz == CTSIZE_INVALID)
	  return 0;
	diff = ((intptr_t)pp - (intptr_t)pp2) / (int32_t)sz;
	/* All valid pointer differences on x64 are in (-2^47, +2^47),
	** which fits into a double without loss of precision.
	*/
	setintptrV(L->top-1, (int32_t)diff);
	return 1;
      } else if (mm == MM_lt) {  /* Pointer comparison (unsigned). */
	setboolV(L->top-1, ((uintptr_t)pp < (uintptr_t)pp2));
	return 1;
      } else {
	lua_assert(mm == MM_le);
	setboolV(L->top-1, ((uintptr_t)pp <= (uintptr_t)pp2));
	return 1;
      }
    }
    if (!((mm == MM_add || mm == MM_sub) && ctype_isnum(ca->ct[1]->info)))
      return 0;
    lj_cconv_ct_ct(cts, ctype_get(cts, CTID_INT_PSZ), ca->ct[1],
		   (uint8_t *)&idx, ca->p[1], 0);
    if (mm == MM_sub) idx = -idx;
  } else if (mm == MM_add && ctype_isnum(ctp->info) &&
      (ctype_isptr(ca->ct[1]->info) || ctype_isrefarray(ca->ct[1]->info))) {
    /* Swap pointer and index. */
    ctp = ca->ct[1]; pp = ca->p[1];
    lj_cconv_ct_ct(cts, ctype_get(cts, CTID_INT_PSZ), ca->ct[0],
		   (uint8_t *)&idx, ca->p[0], 0);
  } else {
    return 0;
  }
  sz = lj_ctype_size(cts, ctype_cid(ctp->info));  /* Element size. */
  if (sz == CTSIZE_INVALID)
    return 0;
  pp += idx*(int32_t)sz;  /* Compute pointer + index. */
  id = lj_ctype_intern(cts, CTINFO(CT_PTR, CTALIGN_PTR|ctype_cid(ctp->info)),
		       CTSIZE_PTR);
  cd = lj_cdata_new(cts, id, CTSIZE_PTR);
  *(uint8_t **)cdataptr(cd) = pp;
  setcdataV(L, L->top-1, cd);
  lj_gc_check(L);
  return 1;
}