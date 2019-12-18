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
typedef  int /*<<< orphan*/  ev_opts_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int zpool_events_clear (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
zpool_do_events_clear(ev_opts_t *opts)
{
	int count, ret;

	ret = zpool_events_clear(g_zfs, &count);
	if (!ret)
		(void) printf(gettext("cleared %d events\n"), count);

	return (ret);
}