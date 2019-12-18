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
typedef  int IROp ;
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
#define  IR_GE 131 
#define  IR_GT 130 
#define  IR_LE 129 
#define  IR_LT 128 
 int lj_str_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 

int lj_ir_strcmp(GCstr *a, GCstr *b, IROp op)
{
  int res = lj_str_cmp(a, b);
  switch (op) {
  case IR_LT: return (res < 0);
  case IR_GE: return (res >= 0);
  case IR_LE: return (res <= 0);
  case IR_GT: return (res > 0);
  default: lua_assert(0); return 0;
  }
}