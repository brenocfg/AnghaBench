#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {scalar_t__ nsp; int /*<<< orphan*/ * stack; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  scalar_t__ MSize ;
typedef  scalar_t__ GPRArg ;
typedef  int /*<<< orphan*/  CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  TYPE_1__ CCallState ;

/* Variables and functions */
 scalar_t__ CCALL_MAXSTACK ; 
 int /*<<< orphan*/  CCF_ARG (int) ; 
 scalar_t__ CTSIZE_PTR ; 
 scalar_t__ ccall_struct_reg (TYPE_1__*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  lj_cconv_ct_tv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int ccall_struct_arg(CCallState *cc, CTState *cts, CType *d, int *rcl,
			    TValue *o, int narg)
{
  GPRArg dp[2];
  dp[0] = dp[1] = 0;
  /* Convert to temp. struct. */
  lj_cconv_ct_tv(cts, d, (uint8_t *)dp, o, CCF_ARG(narg));
  if (ccall_struct_reg(cc, dp, rcl)) {  /* Register overflow? Pass on stack. */
    MSize nsp = cc->nsp, n = rcl[1] ? 2 : 1;
    if (nsp + n > CCALL_MAXSTACK) return 1;  /* Too many arguments. */
    cc->nsp = nsp + n;
    memcpy(&cc->stack[nsp], dp, n*CTSIZE_PTR);
  }
  return 0;  /* Ok. */
}