#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  custom_plans; } ;
struct TYPE_5__ {int /*<<< orphan*/ * methods; } ;
struct TYPE_6__ {int /*<<< orphan*/  subplan; TYPE_1__ csstate; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_2__ GapFillState ;
typedef  TYPE_3__ CustomScan ;

/* Variables and functions */
 int /*<<< orphan*/  T_CustomScanState ; 
 int /*<<< orphan*/  gapfill_state_methods ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ ) ; 
 scalar_t__ newNode (int,int /*<<< orphan*/ ) ; 

Node *
gapfill_state_create(CustomScan *cscan)
{
	GapFillState *state = (GapFillState *) newNode(sizeof(GapFillState), T_CustomScanState);

	state->csstate.methods = &gapfill_state_methods;
	state->subplan = linitial(cscan->custom_plans);

	return (Node *) state;
}