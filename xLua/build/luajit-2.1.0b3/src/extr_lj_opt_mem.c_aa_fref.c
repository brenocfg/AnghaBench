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
typedef  int /*<<< orphan*/  jit_State ;
struct TYPE_4__ {scalar_t__ op2; scalar_t__ op1; } ;
typedef  TYPE_1__ IRIns ;
typedef  int /*<<< orphan*/  AliasRet ;

/* Variables and functions */
 int /*<<< orphan*/  ALIAS_MAY ; 
 int /*<<< orphan*/  ALIAS_MUST ; 
 int /*<<< orphan*/  ALIAS_NO ; 
 scalar_t__ IRFL_TAB_META ; 
 scalar_t__ IRFL_TAB_NOMM ; 
 int /*<<< orphan*/  aa_table (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static AliasRet aa_fref(jit_State *J, IRIns *refa, IRIns *refb)
{
  if (refa->op2 != refb->op2)
    return ALIAS_NO;  /* Different fields. */
  if (refa->op1 == refb->op1)
    return ALIAS_MUST;  /* Same field, same object. */
  else if (refa->op2 >= IRFL_TAB_META && refa->op2 <= IRFL_TAB_NOMM)
    return aa_table(J, refa->op1, refb->op1);  /* Disambiguate tables. */
  else
    return ALIAS_MAY;  /* Same field, possibly different object. */
}