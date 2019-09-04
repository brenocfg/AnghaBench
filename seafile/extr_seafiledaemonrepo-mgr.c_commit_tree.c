#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  commit_id; } ;
struct TYPE_14__ {int /*<<< orphan*/  commit_id; void* client_version; void* device_name; void* parent_id; } ;
struct TYPE_13__ {char* email; TYPE_8__* head; int /*<<< orphan*/  id; } ;
struct TYPE_12__ {int /*<<< orphan*/  branch_mgr; int /*<<< orphan*/  commit_mgr; int /*<<< orphan*/  client_name; int /*<<< orphan*/  client_id; } ;
typedef  TYPE_1__ SeafRepo ;
typedef  TYPE_2__ SeafCommit ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_CLIENT_VERSION ; 
 void* g_strdup (int /*<<< orphan*/ ) ; 
 TYPE_10__* seaf ; 
 int /*<<< orphan*/  seaf_branch_manager_update_branch (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  seaf_branch_set_commit (TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_commit_manager_add_commit (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* seaf_commit_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_commit_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_repo_to_commit (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
commit_tree (SeafRepo *repo, const char *root_id,
             const char *desc, char commit_id[])
{
    SeafCommit *commit;

    commit = seaf_commit_new (NULL, repo->id, root_id,
                              repo->email ? repo->email
                              : "unknown",
                              seaf->client_id,
                              desc, 0);

    commit->parent_id = g_strdup (repo->head->commit_id);

    /* Add this computer's name to commit. */
    commit->device_name = g_strdup(seaf->client_name);
    commit->client_version = g_strdup (SEAFILE_CLIENT_VERSION);

    seaf_repo_to_commit (repo, commit);

    if (seaf_commit_manager_add_commit (seaf->commit_mgr, commit) < 0)
        return -1;

    seaf_branch_set_commit (repo->head, commit->commit_id);
    seaf_branch_manager_update_branch (seaf->branch_mgr, repo->head);

    strcpy (commit_id, commit->commit_id);
    seaf_commit_unref (commit);

    return 0;
}