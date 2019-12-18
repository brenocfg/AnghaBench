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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  jit_State ;
typedef  int /*<<< orphan*/  TRef ;

/* Variables and functions */
 int /*<<< orphan*/  IR_KINT64 ; 
 int /*<<< orphan*/  lj_ir_k64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_k64_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

TRef lj_ir_kint64(jit_State *J, uint64_t u64)
{
  return lj_ir_k64(J, IR_KINT64, lj_ir_k64_find(J, u64));
}