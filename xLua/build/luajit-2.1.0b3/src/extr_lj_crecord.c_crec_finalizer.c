#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int needsnap; } ;
typedef  TYPE_1__ jit_State ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  cTValue ;
typedef  scalar_t__ TRef ;

/* Variables and functions */
 int /*<<< orphan*/  IRCALL_lj_cdata_setfin ; 
 int /*<<< orphan*/  LJ_TRERR_BADTYPE ; 
 int /*<<< orphan*/ * gcval (int /*<<< orphan*/ *) ; 
 scalar_t__ itype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_ir_call (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_ir_kptr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ tvisgcv (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crec_finalizer(jit_State *J, TRef trcd, TRef trfin, cTValue *fin)
{
  if (tvisgcv(fin)) {
    if (!trfin) trfin = lj_ir_kptr(J, gcval(fin));
  } else if (tvisnil(fin)) {
    trfin = lj_ir_kptr(J, NULL);
  } else {
    lj_trace_err(J, LJ_TRERR_BADTYPE);
  }
  lj_ir_call(J, IRCALL_lj_cdata_setfin, trcd,
	     trfin, lj_ir_kint(J, (int32_t)itype(fin)));
  J->needsnap = 1;
}