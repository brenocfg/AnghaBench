#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_2__ jit_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_19__ {scalar_t__ top; } ;
struct TYPE_15__ {scalar_t__ id; } ;
struct TYPE_18__ {int mode; TYPE_1__ val; TYPE_8__* cts; int /*<<< orphan*/ * param; void* p; void* srcname; int /*<<< orphan*/  L; } ;
struct TYPE_17__ {scalar_t__ ctypeid; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  TYPE_3__ GCcdata ;
typedef  scalar_t__ CTypeID ;
typedef  TYPE_4__ CPState ;

/* Variables and functions */
 int CPARSE_MODE_ABSTRACT ; 
 int CPARSE_MODE_NOIMPLICIT ; 
 scalar_t__ CTID_CTYPEID ; 
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_STR ; 
 int /*<<< orphan*/  IR_EQ ; 
 int /*<<< orphan*/  J2G (TYPE_2__*) ; 
 int /*<<< orphan*/  LJ_TRERR_BADTYPE ; 
 TYPE_3__* argv2cdata (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ crec_constructor (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* ctype_ctsG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_cparse (TYPE_4__*) ; 
 int /*<<< orphan*/  lj_ir_kstr (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strV (int /*<<< orphan*/ *) ; 
 void* strdata (int /*<<< orphan*/ *) ; 
 scalar_t__ tref_isstr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CTypeID argv2ctype(jit_State *J, TRef tr, cTValue *o)
{
  if (tref_isstr(tr)) {
    GCstr *s = strV(o);
    CPState cp;
    CTypeID oldtop;
    /* Specialize to the string containing the C type declaration. */
    emitir(IRTG(IR_EQ, IRT_STR), tr, lj_ir_kstr(J, s));
    cp.L = J->L;
    cp.cts = ctype_ctsG(J2G(J));
    oldtop = cp.cts->top;
    cp.srcname = strdata(s);
    cp.p = strdata(s);
    cp.param = NULL;
    cp.mode = CPARSE_MODE_ABSTRACT|CPARSE_MODE_NOIMPLICIT;
    if (lj_cparse(&cp) || cp.cts->top > oldtop)  /* Avoid new struct defs. */
      lj_trace_err(J, LJ_TRERR_BADTYPE);
    return cp.val.id;
  } else {
    GCcdata *cd = argv2cdata(J, tr, o);
    return cd->ctypeid == CTID_CTYPEID ? crec_constructor(J, cd, tr) :
					cd->ctypeid;
  }
}