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
struct seq_file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  stop_time; int /*<<< orphan*/  start_time; int /*<<< orphan*/  max_time; int /*<<< orphan*/  min_time; int /*<<< orphan*/  elapsed_time; int /*<<< orphan*/  num_events; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ kstat_timer_t ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kstat_seq_show_timer(struct seq_file *f, kstat_timer_t *ktp)
{
	seq_printf(f,
	    "%-31s %-8llu %-8llu %-8llu %-8llu %-8llu %-8llu\n",
	    ktp->name, ktp->num_events, ktp->elapsed_time,
	    ktp->min_time, ktp->max_time,
	    ktp->start_time, ktp->stop_time);

	return (0);
}