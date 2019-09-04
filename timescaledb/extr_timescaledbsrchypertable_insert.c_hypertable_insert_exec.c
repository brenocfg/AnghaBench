#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_3__ {int /*<<< orphan*/  custom_ps; } ;
typedef  TYPE_1__ CustomScanState ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecProcNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleTableSlot *
hypertable_insert_exec(CustomScanState *node)
{
	return ExecProcNode(linitial(node->custom_ps));
}