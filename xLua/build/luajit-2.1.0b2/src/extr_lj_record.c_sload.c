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
struct TYPE_5__ {int /*<<< orphan*/ * base; scalar_t__ baseslot; TYPE_1__* L; } ;
typedef  TYPE_2__ jit_State ;
typedef  size_t int32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * base; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  int /*<<< orphan*/  IRType ;

/* Variables and functions */
 int /*<<< orphan*/  IRSLOAD_TYPECHECK ; 
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IR_SLOAD ; 
 int /*<<< orphan*/  TREF_PRI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitir_raw (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ irtype_ispri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  itype2irt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static TRef sload(jit_State *J, int32_t slot)
{
  IRType t = itype2irt(&J->L->base[slot]);
  TRef ref = emitir_raw(IRTG(IR_SLOAD, t), (int32_t)J->baseslot+slot,
			IRSLOAD_TYPECHECK);
  if (irtype_ispri(t)) ref = TREF_PRI(t);  /* Canonicalize primitive refs. */
  J->base[slot] = ref;
  return ref;
}