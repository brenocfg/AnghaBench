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
struct TYPE_3__ {int /*<<< orphan*/  rcnt; int /*<<< orphan*/  wcnt; int /*<<< orphan*/  rlastupdate; int /*<<< orphan*/  rlentime; int /*<<< orphan*/  rtime; int /*<<< orphan*/  wlastupdate; int /*<<< orphan*/  wlentime; int /*<<< orphan*/  wtime; int /*<<< orphan*/  writes; int /*<<< orphan*/  reads; int /*<<< orphan*/  nwritten; int /*<<< orphan*/  nread; } ;
typedef  TYPE_1__ kstat_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kstat_seq_show_io(struct seq_file *f, kstat_io_t *kip)
{
	/* though wlentime & friends are signed, they will never be negative */
	seq_printf(f,
	    "%-8llu %-8llu %-8u %-8u %-8llu %-8llu "
	    "%-8llu %-8llu %-8llu %-8llu %-8u %-8u\n",
	    kip->nread, kip->nwritten,
	    kip->reads, kip->writes,
	    kip->wtime, kip->wlentime, kip->wlastupdate,
	    kip->rtime, kip->rlentime, kip->rlastupdate,
	    kip->wcnt,  kip->rcnt);

	return (0);
}