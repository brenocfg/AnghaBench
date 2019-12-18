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
struct TYPE_4__ {scalar_t__ o; scalar_t__ op1; int op2; } ;
typedef  TYPE_1__ IRIns ;
typedef  int /*<<< orphan*/  AliasRet ;

/* Variables and functions */
 int /*<<< orphan*/  ALIAS_MAY ; 
 int /*<<< orphan*/  ALIAS_MUST ; 
 int /*<<< orphan*/  ALIAS_NO ; 

__attribute__((used)) static AliasRet aa_uref(IRIns *refa, IRIns *refb)
{
  if (refa->o != refb->o)
    return ALIAS_NO;  /* Different UREFx type. */
  if (refa->op1 == refb->op1) {  /* Same function. */
    if (refa->op2 == refb->op2)
      return ALIAS_MUST;  /* Same function, same upvalue idx. */
    else
      return ALIAS_NO;  /* Same function, different upvalue idx. */
  } else {  /* Different functions, check disambiguation hash values. */
    if (((refa->op2 ^ refb->op2) & 0xff))
      return ALIAS_NO;  /* Upvalues with different hash values cannot alias. */
    else
      return ALIAS_MAY;  /* No conclusion can be drawn for same hash value. */
  }
}