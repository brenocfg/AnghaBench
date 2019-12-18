#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* chain; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_6__ {scalar_t__ op1; scalar_t__ op2; scalar_t__ prev; int /*<<< orphan*/  t; } ;
typedef  scalar_t__ IRRef ;
typedef  size_t IROpT ;
typedef  TYPE_2__ IRIns ;

/* Variables and functions */
 TYPE_2__* IR (scalar_t__) ; 
 size_t IRDELTA_L2S ; 
 size_t IR_ALOAD ; 
 int /*<<< orphan*/  irref_isk (scalar_t__) ; 
 scalar_t__ irt_isnil (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_sametype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lj_opt_fwd_wasnonnil(jit_State *J, IROpT loadop, IRRef xref)
{
  /* First check stores. */
  IRRef ref = J->chain[loadop+IRDELTA_L2S];
  while (ref > xref) {
    IRIns *store = IR(ref);
    if (store->op1 == xref) {  /* Same xREF. */
      /* A nil store MAY alias, but a non-nil store MUST alias. */
      return !irt_isnil(store->t);
    } else if (irt_isnil(store->t)) {  /* Must check any nil store. */
      IRRef skref = IR(store->op1)->op2;
      IRRef xkref = IR(xref)->op2;
      /* Same key type MAY alias. Need ALOAD check due to multiple int types. */
      if (loadop == IR_ALOAD || irt_sametype(IR(skref)->t, IR(xkref)->t)) {
	if (skref == xkref || !irref_isk(skref) || !irref_isk(xkref))
	  return 0;  /* A nil store with same const key or var key MAY alias. */
	/* Different const keys CANNOT alias. */
      }  /* Different key types CANNOT alias. */
    }  /* Other non-nil stores MAY alias. */
    ref = store->prev;
  }

  /* Check loads since nothing could be derived from stores. */
  ref = J->chain[loadop];
  while (ref > xref) {
    IRIns *load = IR(ref);
    if (load->op1 == xref) {  /* Same xREF. */
      /* A nil load MAY alias, but a non-nil load MUST alias. */
      return !irt_isnil(load->t);
    }  /* Other non-nil loads MAY alias. */
    ref = load->prev;
  }
  return 0;  /* Nothing derived at all, previous value MAY be nil. */
}