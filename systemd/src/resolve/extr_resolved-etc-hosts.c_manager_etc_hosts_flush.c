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
struct TYPE_3__ {int /*<<< orphan*/  etc_hosts_mtime; int /*<<< orphan*/  etc_hosts; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  USEC_INFINITY ; 
 int /*<<< orphan*/  etc_hosts_free (int /*<<< orphan*/ *) ; 

void manager_etc_hosts_flush(Manager *m) {
        etc_hosts_free(&m->etc_hosts);
        m->etc_hosts_mtime = USEC_INFINITY;
}