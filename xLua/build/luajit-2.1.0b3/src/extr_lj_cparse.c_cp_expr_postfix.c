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
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  L; } ;
struct TYPE_24__ {char tok; int /*<<< orphan*/ * str; TYPE_5__* cts; } ;
struct TYPE_23__ {scalar_t__ u32; int /*<<< orphan*/  id; } ;
struct TYPE_22__ {scalar_t__ size; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTSize ;
typedef  TYPE_2__ CPValue ;
typedef  TYPE_3__ CPState ;

/* Variables and functions */
 char CTOK_DEREF ; 
 char CTOK_IDENT ; 
 scalar_t__ CTSIZE_INVALID ; 
 int /*<<< orphan*/  LJ_ERR_FFI_BADMEMBER ; 
 int /*<<< orphan*/  cp_check (TYPE_3__*,char) ; 
 int /*<<< orphan*/  cp_err_badidx (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cp_err_token (TYPE_3__*,char) ; 
 int /*<<< orphan*/  cp_errmsg (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_expr_comma (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  cp_next (TYPE_3__*) ; 
 scalar_t__ cp_opt (TYPE_3__*,char) ; 
 int /*<<< orphan*/  ctype_cid (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isbitfield (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isconstval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_ispointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_isstruct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_typeid (TYPE_5__*,TYPE_1__*) ; 
 TYPE_1__* lj_ctype_getfield (TYPE_5__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* lj_ctype_rawref (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_ctype_repr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cp_expr_postfix(CPState *cp, CPValue *k)
{
  for (;;) {
    CType *ct;
    if (cp_opt(cp, '[')) {  /* Array/pointer index. */
      CPValue k2;
      cp_expr_comma(cp, &k2);
      ct = lj_ctype_rawref(cp->cts, k->id);
      if (!ctype_ispointer(ct->info)) {
	ct = lj_ctype_rawref(cp->cts, k2.id);
	if (!ctype_ispointer(ct->info))
	  cp_err_badidx(cp, ct);
      }
      cp_check(cp, ']');
      k->u32 = 0;
    } else if (cp->tok == '.' || cp->tok == CTOK_DEREF) {  /* Struct deref. */
      CTSize ofs;
      CType *fct;
      ct = lj_ctype_rawref(cp->cts, k->id);
      if (cp->tok == CTOK_DEREF) {
	if (!ctype_ispointer(ct->info))
	  cp_err_badidx(cp, ct);
	ct = lj_ctype_rawref(cp->cts, ctype_cid(ct->info));
      }
      cp_next(cp);
      if (cp->tok != CTOK_IDENT) cp_err_token(cp, CTOK_IDENT);
      if (!ctype_isstruct(ct->info) || ct->size == CTSIZE_INVALID ||
	  !(fct = lj_ctype_getfield(cp->cts, ct, cp->str, &ofs)) ||
	  ctype_isbitfield(fct->info)) {
	GCstr *s = lj_ctype_repr(cp->cts->L, ctype_typeid(cp->cts, ct), NULL);
	cp_errmsg(cp, 0, LJ_ERR_FFI_BADMEMBER, strdata(s), strdata(cp->str));
      }
      ct = fct;
      k->u32 = ctype_isconstval(ct->info) ? ct->size : 0;
      cp_next(cp);
    } else {
      return;
    }
    k->id = ctype_cid(ct->info);
  }
}