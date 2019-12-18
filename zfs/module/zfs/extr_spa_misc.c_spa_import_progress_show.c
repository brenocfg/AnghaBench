#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_longlong_t ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {char* pool_name; scalar_t__ spa_load_max_txg; scalar_t__ mmp_sec_remaining; scalar_t__ spa_load_state; scalar_t__ pool_guid; } ;
typedef  TYPE_1__ spa_import_progress_t ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
spa_import_progress_show(struct seq_file *f, void *data)
{
	spa_import_progress_t *sip = (spa_import_progress_t *)data;

	seq_printf(f, "%-20llu %-14llu %-14llu %-12llu %s\n",
	    (u_longlong_t)sip->pool_guid, (u_longlong_t)sip->spa_load_state,
	    (u_longlong_t)sip->mmp_sec_remaining,
	    (u_longlong_t)sip->spa_load_max_txg,
	    (sip->pool_name ? sip->pool_name : "-"));

	return (0);
}