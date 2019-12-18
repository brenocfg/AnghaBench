#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  jit_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TRef ;

/* Variables and functions */
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_NUM ; 
 int /*<<< orphan*/  IR_STRTO ; 
 int /*<<< orphan*/  LJ_TRERR_BADTYPE ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_strscan_num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_trace_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strV (int /*<<< orphan*/ *) ; 
 scalar_t__ tref_isstr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TRef conv_str_tonum(jit_State *J, TRef tr, TValue *o)
{
  if (tref_isstr(tr)) {
    tr = emitir(IRTG(IR_STRTO, IRT_NUM), tr, 0);
    /* Would need an inverted STRTO for this rare and useless case. */
    if (!lj_strscan_num(strV(o), o))  /* Convert in-place. Value used below. */
      lj_trace_err(J, LJ_TRERR_BADTYPE);  /* Punt if non-numeric. */
  }
  return tr;
}