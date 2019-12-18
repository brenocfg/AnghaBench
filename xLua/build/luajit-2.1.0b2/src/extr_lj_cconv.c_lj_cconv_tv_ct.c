#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lua_Number ;
typedef  scalar_t__ int32_t ;
struct TYPE_23__ {int /*<<< orphan*/  L; TYPE_1__* g; } ;
struct TYPE_22__ {int info; int size; } ;
struct TYPE_21__ {int /*<<< orphan*/  n; } ;
struct TYPE_20__ {TYPE_2__ tmptv2; } ;
typedef  TYPE_2__ TValue ;
typedef  int /*<<< orphan*/  GCcdata ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_3__ CType ;
typedef  TYPE_4__ CTState ;
typedef  int CTSize ;
typedef  int CTInfo ;

/* Variables and functions */
 int CTF_UNSIGNED ; 
 int /*<<< orphan*/  CTID_DOUBLE ; 
 int /*<<< orphan*/  CTID_INT32 ; 
 int CTSIZE_INVALID ; 
 scalar_t__ LJ_DUALNUM ; 
 int /*<<< orphan*/  cdataptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctype_get (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_isbool (int) ; 
 scalar_t__ ctype_isinteger (int) ; 
 scalar_t__ ctype_isnum (int) ; 
 scalar_t__ ctype_isrefarray (int) ; 
 scalar_t__ ctype_isstruct (int) ; 
 int /*<<< orphan*/  ctype_typeid (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  lj_cconv_ct_ct (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_cdata_new (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * lj_cdata_newref (TYPE_4__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  setboolV (TYPE_2__*,int) ; 
 int /*<<< orphan*/  setcdataV (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setintV (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  setnumV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int tvisnum (TYPE_2__*) ; 

int lj_cconv_tv_ct(CTState *cts, CType *s, CTypeID sid,
		   TValue *o, uint8_t *sp)
{
  CTInfo sinfo = s->info;
  if (ctype_isnum(sinfo)) {
    if (!ctype_isbool(sinfo)) {
      if (ctype_isinteger(sinfo) && s->size > 4) goto copyval;
      if (LJ_DUALNUM && ctype_isinteger(sinfo)) {
	int32_t i;
	lj_cconv_ct_ct(cts, ctype_get(cts, CTID_INT32), s,
		       (uint8_t *)&i, sp, 0);
	if ((sinfo & CTF_UNSIGNED) && i < 0)
	  setnumV(o, (lua_Number)(uint32_t)i);
	else
	  setintV(o, i);
      } else {
	lj_cconv_ct_ct(cts, ctype_get(cts, CTID_DOUBLE), s,
		       (uint8_t *)&o->n, sp, 0);
	/* Numbers are NOT canonicalized here! Beware of uninitialized data. */
	lua_assert(tvisnum(o));
      }
    } else {
      uint32_t b = s->size == 1 ? (*sp != 0) : (*(int *)sp != 0);
      setboolV(o, b);
      setboolV(&cts->g->tmptv2, b);  /* Remember for trace recorder. */
    }
    return 0;
  } else if (ctype_isrefarray(sinfo) || ctype_isstruct(sinfo)) {
    /* Create reference. */
    setcdataV(cts->L, o, lj_cdata_newref(cts, sp, sid));
    return 1;  /* Need GC step. */
  } else {
    GCcdata *cd;
    CTSize sz;
  copyval:  /* Copy value. */
    sz = s->size;
    lua_assert(sz != CTSIZE_INVALID);
    /* Attributes are stripped, qualifiers are kept (but mostly ignored). */
    cd = lj_cdata_new(cts, ctype_typeid(cts, s), sz);
    setcdataV(cts->L, o, cd);
    memcpy(cdataptr(cd), sp, sz);
    return 1;  /* Need GC step. */
  }
}