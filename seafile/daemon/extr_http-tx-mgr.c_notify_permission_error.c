#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* http_tx_mgr; } ;
struct TYPE_8__ {int /*<<< orphan*/  folder_perm_error_regex; int /*<<< orphan*/  locked_error_regex; } ;
struct TYPE_7__ {void* error; int /*<<< orphan*/  repo_name; int /*<<< orphan*/  repo_id; } ;
struct TYPE_6__ {TYPE_3__* priv; } ;
typedef  TYPE_2__ HttpTxTask ;
typedef  TYPE_3__ HttpTxPriv ;
typedef  int /*<<< orphan*/  GMatchInfo ;

/* Variables and functions */
 void* SYNC_ERROR_ID_FILE_LOCKED ; 
 void* SYNC_ERROR_ID_FOLDER_PERM_DENIED ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_match_info_fetch (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_match_info_free (int /*<<< orphan*/ *) ; 
 scalar_t__ g_regex_match (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_4__* seaf ; 
 int /*<<< orphan*/  seaf_repo_manager_record_sync_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static void
notify_permission_error (HttpTxTask *task, const char *error_str)
{
    HttpTxPriv *priv = seaf->http_tx_mgr->priv;
    GMatchInfo *match_info;
    char *path;

    if (g_regex_match (priv->locked_error_regex, error_str, 0, &match_info)) {
        path = g_match_info_fetch (match_info, 1);
        seaf_repo_manager_record_sync_error (task->repo_id, task->repo_name, path,
                                             SYNC_ERROR_ID_FILE_LOCKED);
        g_free (path);

        /* Set more accurate error. */
        task->error = SYNC_ERROR_ID_FILE_LOCKED;
    } else if (g_regex_match (priv->folder_perm_error_regex, error_str, 0, &match_info)) {
        path = g_match_info_fetch (match_info, 1);
        /* The path returned by server begins with '/'. */
        seaf_repo_manager_record_sync_error (task->repo_id, task->repo_name,
                                             (path[0] == '/') ? (path + 1) : path,
                                             SYNC_ERROR_ID_FOLDER_PERM_DENIED);
        g_free (path);

        task->error = SYNC_ERROR_ID_FOLDER_PERM_DENIED;
    }

    g_match_info_free (match_info);
}