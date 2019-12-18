#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  plan; } ;
struct TYPE_7__ {int /*<<< orphan*/ * methods; } ;
struct TYPE_9__ {int /*<<< orphan*/ * subplan; TYPE_1__ csstate; } ;
struct TYPE_8__ {int /*<<< orphan*/  custom_plans; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_2__ CustomScan ;
typedef  TYPE_3__ ConstraintAwareAppendState ;
typedef  TYPE_4__ Append ;

/* Variables and functions */
 int /*<<< orphan*/  T_CustomScanState ; 
 int /*<<< orphan*/  constraint_aware_append_state_methods ; 
 TYPE_4__* linitial (int /*<<< orphan*/ ) ; 
 scalar_t__ newNode (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *
constraint_aware_append_state_create(CustomScan *cscan)
{
	ConstraintAwareAppendState *state;
	Append *append = linitial(cscan->custom_plans);

	state = (ConstraintAwareAppendState *) newNode(sizeof(ConstraintAwareAppendState),
												   T_CustomScanState);
	state->csstate.methods = &constraint_aware_append_state_methods;
	state->subplan = &append->plan;

	return (Node *) state;
}