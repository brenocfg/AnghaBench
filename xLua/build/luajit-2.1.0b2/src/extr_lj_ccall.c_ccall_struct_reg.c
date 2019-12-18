#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {scalar_t__ ngpr; scalar_t__ nfpr; TYPE_1__* fpr; void** gpr; } ;
struct TYPE_4__ {void** l; } ;
typedef  scalar_t__ MSize ;
typedef  void* GPRArg ;
typedef  TYPE_2__ CCallState ;

/* Variables and functions */
 scalar_t__ CCALL_NARG_FPR ; 
 scalar_t__ CCALL_NARG_GPR ; 
 int CCALL_RCL_INT ; 
 int CCALL_RCL_MEM ; 
 int CCALL_RCL_SSE ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static int ccall_struct_reg(CCallState *cc, GPRArg *dp, int *rcl)
{
  MSize ngpr = cc->ngpr, nfpr = cc->nfpr;
  uint32_t i;
  for (i = 0; i < 2; i++) {
    lua_assert(!(rcl[i] & CCALL_RCL_MEM));
    if ((rcl[i] & CCALL_RCL_INT)) {  /* Integer class takes precedence. */
      if (ngpr >= CCALL_NARG_GPR) return 1;  /* Register overflow. */
      cc->gpr[ngpr++] = dp[i];
    } else if ((rcl[i] & CCALL_RCL_SSE)) {
      if (nfpr >= CCALL_NARG_FPR) return 1;  /* Register overflow. */
      cc->fpr[nfpr++].l[0] = dp[i];
    }
  }
  cc->ngpr = ngpr; cc->nfpr = nfpr;
  return 0;  /* Ok. */
}