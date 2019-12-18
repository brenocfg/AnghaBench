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
typedef  int /*<<< orphan*/  OrderedSet ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fflush_and_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs_unlocked (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ordered_set_isempty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_resolv_conf_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_stub_resolv_conf_contents(FILE *f, OrderedSet *dns, OrderedSet *domains) {
        fputs_unlocked("# This file is managed by man:systemd-resolved(8). Do not edit.\n"
                       "#\n"
                       "# This is a dynamic resolv.conf file for connecting local clients to the\n"
                       "# internal DNS stub resolver of systemd-resolved. This file lists all\n"
                       "# configured search domains.\n"
                       "#\n"
                       "# Run \"resolvectl status\" to see details about the uplink DNS servers\n"
                       "# currently in use.\n"
                       "#\n"
                       "# Third party programs must not access this file directly, but only through the\n"
                       "# symlink at /etc/resolv.conf. To manage man:resolv.conf(5) in a different way,\n"
                       "# replace this symlink by a static file or a different symlink.\n"
                       "#\n"
                       "# See man:systemd-resolved.service(8) for details about the supported modes of\n"
                       "# operation for /etc/resolv.conf.\n"
                       "\n"
                       "nameserver 127.0.0.53\n"
                       "options edns0\n", f);

        if (!ordered_set_isempty(domains))
                write_resolv_conf_search(domains, f);

        return fflush_and_check(f);
}