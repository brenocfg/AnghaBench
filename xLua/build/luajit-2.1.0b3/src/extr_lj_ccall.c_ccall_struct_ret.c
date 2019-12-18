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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {TYPE_1__* fpr; int /*<<< orphan*/ * gpr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * l; } ;
typedef  scalar_t__ MSize ;
typedef  int /*<<< orphan*/  GPRArg ;
typedef  int /*<<< orphan*/  CTSize ;
typedef  TYPE_2__ CCallState ;

/* Variables and functions */
 int CCALL_RCL_INT ; 
 int CCALL_RCL_SSE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccall_struct_ret(CCallState *cc, int *rcl, uint8_t *dp, CTSize sz)
{
  GPRArg sp[2];
  MSize ngpr = 0, nfpr = 0;
  uint32_t i;
  for (i = 0; i < 2; i++) {
    if ((rcl[i] & CCALL_RCL_INT)) {  /* Integer class takes precedence. */
      sp[i] = cc->gpr[ngpr++];
    } else if ((rcl[i] & CCALL_RCL_SSE)) {
      sp[i] = cc->fpr[nfpr++].l[0];
    }
  }
  memcpy(dp, sp, sz);
}