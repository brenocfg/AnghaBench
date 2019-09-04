#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ sec; } ;
struct cache_entry {int ce_mode; TYPE_1__ ce_mtime; int /*<<< orphan*/  sha1; } ;
typedef  int gboolean ;
struct TYPE_18__ {int mode; scalar_t__ mtime; int /*<<< orphan*/  sha1; } ;
struct TYPE_17__ {int repo_version; TYPE_3__* http_task; int /*<<< orphan*/ * crypt; } ;
struct TYPE_16__ {char* path; void* force_conflict; void* no_checkout; TYPE_6__* de; struct cache_entry* ce; } ;
struct TYPE_15__ {scalar_t__ state; } ;
struct TYPE_14__ {scalar_t__ st_mtime; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  TYPE_2__ SeafStat ;
typedef  TYPE_3__ HttpTxTask ;
typedef  TYPE_4__ FileTxTask ;
typedef  TYPE_5__ FileTxData ;
typedef  TYPE_6__ DiffEntry ;

/* Variables and functions */
 int FALSE ; 
 int FETCH_CHECKOUT_CANCELED ; 
 int FETCH_CHECKOUT_SUCCESS ; 
 int FETCH_CHECKOUT_TRANSFER_ERROR ; 
 scalar_t__ HTTP_TASK_STATE_CANCELED ; 
 int S_IFMT ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/  chmod (char*,int) ; 
 scalar_t__ compare_file_content (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fill_stat_cache_info (struct cache_entry*,TYPE_2__*) ; 
 int http_tx_task_download_file_blocks (TYPE_3__*,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rawdata_to_hex (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  seaf_debug (char*) ; 
 int /*<<< orphan*/  seaf_message (char*,char*) ; 
 int /*<<< orphan*/  seaf_set_file_time (char*,scalar_t__) ; 
 scalar_t__ seaf_stat (char*,TYPE_2__*) ; 

__attribute__((used)) static int
fetch_file_http (FileTxData *data, FileTxTask *file_task)
{
    int repo_version = data->repo_version;
    struct cache_entry *ce = file_task->ce;
    DiffEntry *de = file_task->de;
    SeafileCrypt *crypt = data->crypt;
    char *path = file_task->path;
    HttpTxTask *http_task = data->http_task;
    SeafStat st;
    char file_id[41];
    gboolean path_exists = FALSE;

    rawdata_to_hex (de->sha1, file_id, 20);

    path_exists = (seaf_stat (path, &st) == 0);

    if (path_exists && S_ISREG(st.st_mode)) {
        if (st.st_mtime == ce->ce_mtime.sec) {
            /* Worktree and index are consistent. */
            if (memcmp (de->sha1, ce->sha1, 20) == 0) {
                seaf_debug ("wt and index are consistent. no need to checkout.\n");
                file_task->no_checkout = TRUE;

                /* Update mode if necessary. */
                if (de->mode != ce->ce_mode) {
#ifndef WIN32
                    chmod (path, de->mode & ~S_IFMT);
                    ce->ce_mode = de->mode;
#endif
                }

                /* Update mtime if necessary. */
                if (de->mtime != ce->ce_mtime.sec) {
                    seaf_set_file_time (path, de->mtime);
                    ce->ce_mtime.sec = de->mtime;
                }

                fill_stat_cache_info (ce, &st);

                return FETCH_CHECKOUT_SUCCESS;
            }
            /* otherwise we have to checkout the file. */
        } else {
            if (compare_file_content (path, &st, de->sha1, crypt, repo_version) == 0) {
                /* This happens after the worktree file was updated,
                 * but the index was not. Just need to update the index.
                 */
                seaf_debug ("update index only.\n");
                file_task->no_checkout = TRUE;
                fill_stat_cache_info (ce, &st);
                return FETCH_CHECKOUT_SUCCESS;
            } else {
                /* Conflict. The worktree file was updated by the user. */
                seaf_message ("File %s is updated by user. "
                              "Will checkout to conflict file later.\n", path);
                file_task->force_conflict = TRUE;
            }
        }
    }

    /* Download the blocks of this file. */
    int rc;
    rc = http_tx_task_download_file_blocks (http_task, file_id);
    if (http_task->state == HTTP_TASK_STATE_CANCELED) {
        return FETCH_CHECKOUT_CANCELED;
    }
    if (rc < 0) {
        return FETCH_CHECKOUT_TRANSFER_ERROR;
    }

    return FETCH_CHECKOUT_SUCCESS;
}