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
typedef  int /*<<< orphan*/  SeafRepoManager ;

/* Variables and functions */
 int /*<<< orphan*/  REPO_PROP_RELAY_ADDR ; 
 int /*<<< orphan*/  REPO_PROP_RELAY_PORT ; 
 char* load_repo_property (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

void
seaf_repo_manager_get_repo_relay_info (SeafRepoManager *mgr,
                                       const char *repo_id,
                                       char **relay_addr,
                                       char **relay_port)
{
    char *addr, *port;

    addr = load_repo_property (mgr, repo_id, REPO_PROP_RELAY_ADDR);
    port = load_repo_property (mgr, repo_id, REPO_PROP_RELAY_PORT);

    if (relay_addr && addr)
        *relay_addr = addr;
    if (relay_port && port)
        *relay_port = port;
}