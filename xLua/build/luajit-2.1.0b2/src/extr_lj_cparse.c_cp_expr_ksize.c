#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int u32; } ;
typedef  int CTSize ;
typedef  TYPE_1__ CPValue ;
typedef  int /*<<< orphan*/  CPState ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_FFI_INVSIZE ; 
 int /*<<< orphan*/  cp_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_expr_kint (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static CTSize cp_expr_ksize(CPState *cp)
{
  CPValue k;
  cp_expr_kint(cp, &k);
  if (k.u32 >= 0x80000000u) cp_err(cp, LJ_ERR_FFI_INVSIZE);
  return k.u32;
}