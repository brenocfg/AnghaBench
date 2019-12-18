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
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static int
spa_mmp_history_show_header(struct seq_file *f)
{
	seq_printf(f, "%-10s %-10s %-10s %-6s %-10s %-12s %-24s "
	    "%-10s %s\n", "id", "txg", "timestamp", "error", "duration",
	    "mmp_delay", "vdev_guid", "vdev_label", "vdev_path");
	return (0);
}