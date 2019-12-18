#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  num_append_subplans; } ;
struct TYPE_10__ {int /*<<< orphan*/  custom_private; } ;
struct TYPE_7__ {scalar_t__ plan; } ;
struct TYPE_8__ {TYPE_1__ ps; } ;
struct TYPE_9__ {TYPE_2__ ss; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ExplainState ;
typedef  TYPE_3__ CustomScanState ;
typedef  TYPE_4__ CustomScan ;
typedef  TYPE_5__ ConstraintAwareAppendState ;

/* Variables and functions */
 int /*<<< orphan*/  ExplainPropertyIntegerCompat (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExplainPropertyText (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linitial_oid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ca_append_explain(CustomScanState *node, List *ancestors, ExplainState *es)
{
	CustomScan *cscan = (CustomScan *) node->ss.ps.plan;
	ConstraintAwareAppendState *state = (ConstraintAwareAppendState *) node;
	Oid relid = linitial_oid(linitial(cscan->custom_private));

	ExplainPropertyText("Hypertable", get_rel_name(relid), es);
	ExplainPropertyIntegerCompat("Chunks left after exclusion",
								 NULL,
								 state->num_append_subplans,
								 es);
}