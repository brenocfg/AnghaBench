#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  custom_private; int /*<<< orphan*/  custom_plans; } ;
struct TYPE_6__ {int /*<<< orphan*/ * methods; } ;
struct TYPE_8__ {TYPE_2__* mt; TYPE_1__ cscan_state; } ;
struct TYPE_7__ {scalar_t__ arbiterIndexes; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_2__ ModifyTable ;
typedef  TYPE_3__ HypertableInsertState ;
typedef  TYPE_4__ CustomScan ;

/* Variables and functions */
 int /*<<< orphan*/  T_CustomScanState ; 
 int /*<<< orphan*/  hypertable_insert_state_methods ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 
 scalar_t__ newNode (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *
hypertable_insert_state_create(CustomScan *cscan)
{
	HypertableInsertState *state;

	state = (HypertableInsertState *) newNode(sizeof(HypertableInsertState), T_CustomScanState);
	state->cscan_state.methods = &hypertable_insert_state_methods;
	state->mt = (ModifyTable *) linitial(cscan->custom_plans);

	/*
	 * Restore ModifyTable arbiterIndexes to the original value
	 * this is necessary in case this plan gets executed multiple
	 * times in a prepared statement.
	 */
	state->mt->arbiterIndexes = linitial(cscan->custom_private);

	return (Node *) state;
}