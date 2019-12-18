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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static int
spa_import_progress_show_header(struct seq_file *f)
{
	seq_printf(f, "%-20s %-14s %-14s %-12s %s\n", "pool_guid",
	    "load_state", "multihost_secs", "max_txg",
	    "pool_name");
	return (0);
}