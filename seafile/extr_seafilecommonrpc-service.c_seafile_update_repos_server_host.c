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
struct TYPE_2__ {int /*<<< orphan*/  repo_mgr; } ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_ARGS ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* seaf ; 
 int seaf_repo_manager_update_repos_server_host (int /*<<< orphan*/ ,char const*,char const*,char const*) ; 

int
seafile_update_repos_server_host (const char *old_host,
                                  const char *new_host,
                                  const char *new_server_url,
                                  GError **error)
{
    if (!old_host || !new_host || !new_server_url) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Argument should not be null");
        return -1;
    }

    return seaf_repo_manager_update_repos_server_host(
        seaf->repo_mgr, old_host, new_host, new_server_url);
}