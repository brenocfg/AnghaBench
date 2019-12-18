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
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static int
dbuf_stats_hash_table_headers(char *buf, size_t size)
{
	(void) snprintf(buf, size,
	    "%-96s | %-119s | %s\n"
	    "%-16s %-8s %-8s %-8s %-8s %-10s %-8s %-5s %-5s %-7s %3s | "
	    "%-5s %-5s %-9s %-6s %-8s %-12s "
	    "%-6s %-6s %-6s %-6s %-6s %-8s %-8s %-8s %-6s | "
	    "%-6s %-6s %-8s %-8s %-6s %-6s %-6s %-8s %-8s\n",
	    "dbuf", "arcbuf", "dnode", "pool", "objset", "object", "level",
	    "blkid", "offset", "dbsize", "meta", "state", "dbholds", "dbc",
	    "list", "atype", "flags", "count", "asize", "access",
	    "mru", "gmru", "mfu", "gmfu", "l2", "l2_dattr", "l2_asize",
	    "l2_comp", "aholds", "dtype", "btype", "data_bs", "meta_bs",
	    "bsize", "lvls", "dholds", "blocks", "dsize");

	return (0);
}