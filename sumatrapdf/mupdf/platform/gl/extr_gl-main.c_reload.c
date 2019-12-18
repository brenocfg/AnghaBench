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
 scalar_t__ doc ; 
 int /*<<< orphan*/  load_document () ; 
 int /*<<< orphan*/  load_page () ; 
 int /*<<< orphan*/  render_page () ; 
 int /*<<< orphan*/  save_accelerator () ; 
 int /*<<< orphan*/  save_history () ; 
 int /*<<< orphan*/  update_title () ; 

void reload(void)
{
	save_history();
	save_accelerator();
	load_document();
	if (doc)
	{
		load_page();
		render_page();
		update_title();
	}
}