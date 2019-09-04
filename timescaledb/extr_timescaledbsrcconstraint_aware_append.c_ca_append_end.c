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
struct TYPE_3__ {scalar_t__ custom_ps; } ;
typedef  TYPE_1__ CustomScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecEndNode (int /*<<< orphan*/ ) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  linitial (scalar_t__) ; 

__attribute__((used)) static void
ca_append_end(CustomScanState *node)
{
	if (node->custom_ps != NIL)
	{
		ExecEndNode(linitial(node->custom_ps));
	}
}