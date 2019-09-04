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
struct options_table_entry {int dummy; } ;
struct options_entry {struct options_table_entry const* tableentry; } ;

/* Variables and functions */

const struct options_table_entry *
options_table_entry(struct options_entry *o)
{
	return (o->tableentry);
}