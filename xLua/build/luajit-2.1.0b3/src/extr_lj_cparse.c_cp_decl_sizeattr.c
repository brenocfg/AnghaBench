#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  tmask; } ;
typedef  int /*<<< orphan*/  CTSize ;
typedef  TYPE_1__ CPState ;

/* Variables and functions */
 int /*<<< orphan*/  CPNS_DEFAULT ; 
 int /*<<< orphan*/  cp_check (TYPE_1__*,char) ; 
 int /*<<< orphan*/  cp_expr_ksize (TYPE_1__*) ; 

__attribute__((used)) static CTSize cp_decl_sizeattr(CPState *cp)
{
  CTSize sz;
  uint32_t oldtmask = cp->tmask;
  cp->tmask = CPNS_DEFAULT;  /* Required for expression evaluator. */
  cp_check(cp, '(');
  sz = cp_expr_ksize(cp);
  cp->tmask = oldtmask;
  cp_check(cp, ')');
  return sz;
}