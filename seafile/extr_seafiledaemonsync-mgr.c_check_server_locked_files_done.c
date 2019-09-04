#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* gint64 ;
struct TYPE_14__ {int /*<<< orphan*/  filelock_mgr; int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_13__ {TYPE_3__* data; struct TYPE_13__* next; } ;
struct TYPE_12__ {TYPE_5__* results; int /*<<< orphan*/  success; } ;
struct TYPE_11__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  locked_files; } ;
struct TYPE_10__ {scalar_t__ last_check_locked_files_time; int /*<<< orphan*/  locked_files_not_supported; int /*<<< orphan*/  checking_locked_files; } ;
struct TYPE_9__ {scalar_t__ in_sync; } ;
typedef  TYPE_1__ SyncInfo ;
typedef  TYPE_2__ HttpServerState ;
typedef  TYPE_3__ HttpLockedFilesRes ;
typedef  TYPE_4__ HttpLockedFiles ;
typedef  TYPE_5__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* get_sync_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* seaf ; 
 int /*<<< orphan*/  seaf_filelock_manager_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_filelock_manager_update_timestamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
check_server_locked_files_done (HttpLockedFiles *result, void *user_data)
{
    HttpServerState *server_state = user_data;
    GList *ptr;
    HttpLockedFilesRes *locked_res;
    gint64 now = (gint64)time(NULL);

    server_state->checking_locked_files = FALSE;

    if (!result->success) {
        /* If on star-up we find that checking locked files fails,
         * we assume the server doesn't support it.
         */
        if (server_state->last_check_locked_files_time == 0)
            server_state->locked_files_not_supported = TRUE;
        server_state->last_check_locked_files_time = now;
        return;
    }

    SyncInfo *info;
    for (ptr = result->results; ptr; ptr = ptr->next) {
        locked_res = ptr->data;

        info = get_sync_info (seaf->sync_mgr, locked_res->repo_id);
        if (info->in_sync)
            continue;

        seaf_filelock_manager_update (seaf->filelock_mgr,
                                      locked_res->repo_id,
                                      locked_res->locked_files);

        seaf_filelock_manager_update_timestamp (seaf->filelock_mgr,
                                                locked_res->repo_id,
                                                locked_res->timestamp);
    }

    server_state->last_check_locked_files_time = now;
}