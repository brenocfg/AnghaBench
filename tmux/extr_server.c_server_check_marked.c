#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int cmd_find_valid_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  marked_pane ; 

int
server_check_marked(void)
{
	return (cmd_find_valid_state(&marked_pane));
}