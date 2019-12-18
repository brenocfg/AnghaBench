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
typedef  int /*<<< orphan*/  SearpcClient ;
typedef  int /*<<< orphan*/  GObject ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_TYPE_REPO ; 
 int /*<<< orphan*/  g_return_val_if_fail (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * searpc_client_call__object (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,char*,char const*) ; 

GObject *
seafile_get_repo (SearpcClient *client,
                  const char *repo_id,
                  GError **error)
{
    g_return_val_if_fail (client && repo_id, NULL);

    return searpc_client_call__object (
        client, "seafile_get_repo", SEAFILE_TYPE_REPO, error,
        1, "string", repo_id);
}