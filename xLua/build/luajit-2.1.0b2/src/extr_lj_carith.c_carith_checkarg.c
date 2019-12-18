#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_25__ {TYPE_2__* top; TYPE_2__* base; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_29__ {int /*<<< orphan*/ ** p; TYPE_4__** ct; } ;
struct TYPE_28__ {int /*<<< orphan*/  size; int /*<<< orphan*/  info; } ;
struct TYPE_27__ {int ctypeid; } ;
struct TYPE_26__ {int /*<<< orphan*/  n; int /*<<< orphan*/  i; } ;
typedef  TYPE_2__ TValue ;
typedef  int MSize ;
typedef  TYPE_3__ GCcdata ;
typedef  int CTypeID ;
typedef  TYPE_4__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  int /*<<< orphan*/  CTSize ;
typedef  TYPE_5__ CDArith ;

/* Variables and functions */
 int CTALIGN_PTR ; 
 int /*<<< orphan*/  CTID_DOUBLE ; 
 int /*<<< orphan*/  CTID_INT32 ; 
 int /*<<< orphan*/  CTID_P_VOID ; 
 int /*<<< orphan*/  CTINFO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CTSIZE_PTR ; 
 int /*<<< orphan*/  CT_PTR ; 
 int /*<<< orphan*/  LUA_TCDATA ; 
 TYPE_3__* cdataV (TYPE_2__*) ; 
 scalar_t__ cdata_getptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cdataptr (TYPE_3__*) ; 
 void* ctype_child (int /*<<< orphan*/ *,TYPE_4__*) ; 
 void* ctype_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isconstval (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isenum (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isptr (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isref (int /*<<< orphan*/ ) ; 
 TYPE_4__* ctype_raw (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* ctype_rawchild (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* lj_ctype_getfield (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_ctype_intern (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_argt (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strV (TYPE_2__*) ; 
 scalar_t__ strVdata (TYPE_2__*) ; 
 scalar_t__ tviscdata (TYPE_2__*) ; 
 scalar_t__ tvisint (TYPE_2__*) ; 
 scalar_t__ tvisnil (TYPE_2__*) ; 
 scalar_t__ tvisnum (TYPE_2__*) ; 
 scalar_t__ tvisstr (TYPE_2__*) ; 

__attribute__((used)) static int carith_checkarg(lua_State *L, CTState *cts, CDArith *ca)
{
  TValue *o = L->base;
  int ok = 1;
  MSize i;
  if (o+1 >= L->top)
    lj_err_argt(L, 1, LUA_TCDATA);
  for (i = 0; i < 2; i++, o++) {
    if (tviscdata(o)) {
      GCcdata *cd = cdataV(o);
      CTypeID id = (CTypeID)cd->ctypeid;
      CType *ct = ctype_raw(cts, id);
      uint8_t *p = (uint8_t *)cdataptr(cd);
      if (ctype_isptr(ct->info)) {
	p = (uint8_t *)cdata_getptr(p, ct->size);
	if (ctype_isref(ct->info)) ct = ctype_rawchild(cts, ct);
      } else if (ctype_isfunc(ct->info)) {
	p = (uint8_t *)*(void **)p;
	ct = ctype_get(cts,
	  lj_ctype_intern(cts, CTINFO(CT_PTR, CTALIGN_PTR|id), CTSIZE_PTR));
      }
      if (ctype_isenum(ct->info)) ct = ctype_child(cts, ct);
      ca->ct[i] = ct;
      ca->p[i] = p;
    } else if (tvisint(o)) {
      ca->ct[i] = ctype_get(cts, CTID_INT32);
      ca->p[i] = (uint8_t *)&o->i;
    } else if (tvisnum(o)) {
      ca->ct[i] = ctype_get(cts, CTID_DOUBLE);
      ca->p[i] = (uint8_t *)&o->n;
    } else if (tvisnil(o)) {
      ca->ct[i] = ctype_get(cts, CTID_P_VOID);
      ca->p[i] = (uint8_t *)0;
    } else if (tvisstr(o)) {
      TValue *o2 = i == 0 ? o+1 : o-1;
      CType *ct = ctype_raw(cts, cdataV(o2)->ctypeid);
      ca->ct[i] = NULL;
      ca->p[i] = (uint8_t *)strVdata(o);
      ok = 0;
      if (ctype_isenum(ct->info)) {
	CTSize ofs;
	CType *cct = lj_ctype_getfield(cts, ct, strV(o), &ofs);
	if (cct && ctype_isconstval(cct->info)) {
	  ca->ct[i] = ctype_child(cts, cct);
	  ca->p[i] = (uint8_t *)&cct->size;  /* Assumes ct does not grow. */
	  ok = 1;
	} else {
	  ca->ct[1-i] = ct;  /* Use enum to improve error message. */
	  ca->p[1-i] = NULL;
	  break;
	}
      }
    } else {
      ca->ct[i] = NULL;
      ca->p[i] = (void *)(intptr_t)1;  /* To make it unequal. */
      ok = 0;
    }
  }
  return ok;
}