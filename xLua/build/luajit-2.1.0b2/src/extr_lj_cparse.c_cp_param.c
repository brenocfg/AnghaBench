#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * base; int /*<<< orphan*/ * top; } ;
struct TYPE_13__ {scalar_t__ id; int /*<<< orphan*/  i32; } ;
struct TYPE_15__ {TYPE_2__ val; TYPE_5__* L; TYPE_1__* cts; int /*<<< orphan*/ * ct; int /*<<< orphan*/  str; int /*<<< orphan*/ * param; } ;
struct TYPE_14__ {scalar_t__ ctypeid; } ;
struct TYPE_12__ {int /*<<< orphan*/ * tab; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_3__ GCcdata ;
typedef  scalar_t__ CTypeID ;
typedef  char CPToken ;
typedef  TYPE_4__ CPState ;
typedef  char CPChar ;

/* Variables and functions */
 scalar_t__ CTID_CTYPEID ; 
 scalar_t__ CTID_INT32 ; 
 char CTOK_IDENT ; 
 char CTOK_INTEGER ; 
 int /*<<< orphan*/  LJ_ERR_FFI_NUMPARAM ; 
 int /*<<< orphan*/  LJ_ERR_XSYNTAX ; 
 TYPE_3__* cdataV (int /*<<< orphan*/ *) ; 
 scalar_t__ cdataptr (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_err (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_errmsg (TYPE_4__*,char,int /*<<< orphan*/ ) ; 
 char cp_get (TYPE_4__*) ; 
 scalar_t__ lj_char_isident (char) ; 
 int /*<<< orphan*/  lj_err_argtype (TYPE_5__*,int,char*) ; 
 int /*<<< orphan*/  numberVint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tviscdata (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnumber (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static CPToken cp_param(CPState *cp)
{
  CPChar c = cp_get(cp);
  TValue *o = cp->param;
  if (lj_char_isident(c) || c == '$')  /* Reserve $xyz for future extensions. */
    cp_errmsg(cp, c, LJ_ERR_XSYNTAX);
  if (!o || o >= cp->L->top)
    cp_err(cp, LJ_ERR_FFI_NUMPARAM);
  cp->param = o+1;
  if (tvisstr(o)) {
    cp->str = strV(o);
    cp->val.id = 0;
    cp->ct = &cp->cts->tab[0];
    return CTOK_IDENT;
  } else if (tvisnumber(o)) {
    cp->val.i32 = numberVint(o);
    cp->val.id = CTID_INT32;
    return CTOK_INTEGER;
  } else {
    GCcdata *cd;
    if (!tviscdata(o))
      lj_err_argtype(cp->L, (int)(o-cp->L->base)+1, "type parameter");
    cd = cdataV(o);
    if (cd->ctypeid == CTID_CTYPEID)
      cp->val.id = *(CTypeID *)cdataptr(cd);
    else
      cp->val.id = cd->ctypeid;
    return '$';
  }
}