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
struct TYPE_4__ {int /*<<< orphan*/  n; } ;
typedef  TYPE_1__ cTValue ;
typedef  int /*<<< orphan*/  Reg ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  XO_MOVSD ; 
 int /*<<< orphan*/  XO_XORPS ; 
 int /*<<< orphan*/  emit_rma (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tvispzero (TYPE_1__*) ; 

__attribute__((used)) static void emit_loadn(ASMState *as, Reg r, cTValue *tv)
{
  if (tvispzero(tv))  /* Use xor only for +0. */
    emit_rr(as, XO_XORPS, r, r);
  else
    emit_rma(as, XO_MOVSD, r, &tv->n);
}