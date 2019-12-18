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
struct TYPE_3__ {int /*<<< orphan*/  custom_plans; int /*<<< orphan*/  custom_private; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ CustomScan ;

/* Variables and functions */
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linitial_oid (int /*<<< orphan*/ ) ; 
 scalar_t__ ts_chunk_dispatch_state_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *
create_chunk_dispatch_state(CustomScan *cscan)
{
	return (Node *) ts_chunk_dispatch_state_create(linitial_oid(cscan->custom_private),
												   linitial(cscan->custom_plans));
}