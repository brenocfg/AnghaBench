#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_11__ ;

/* Type definitions */
struct index_state {int dummy; } ;
typedef  int /*<<< orphan*/  gint64 ;
typedef  void* gboolean ;
struct TYPE_24__ {void* partial_commit; int /*<<< orphan*/  q_lock; int /*<<< orphan*/  event_q; } ;
typedef  TYPE_1__ WTStatus ;
struct TYPE_25__ {int ev_type; int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ WTEvent ;
struct TYPE_26__ {int /*<<< orphan*/  id; int /*<<< orphan*/  worktree; int /*<<< orphan*/  is_readonly; int /*<<< orphan*/  changeset; int /*<<< orphan*/  name; } ;
struct TYPE_23__ {int /*<<< orphan*/  filelock_mgr; int /*<<< orphan*/  sync_mgr; int /*<<< orphan*/  wt_monitor; } ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  TYPE_3__ SeafRepo ;
typedef  int /*<<< orphan*/  LockedFileSet ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_STATUS_DELETED ; 
 void* FALSE ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_UPDATE_TO_READ_ONLY_REPO ; 
#define  WT_EVENT_ATTRIB 133 
#define  WT_EVENT_CREATE_OR_UPDATE 132 
#define  WT_EVENT_DELETE 131 
#define  WT_EVENT_OVERFLOW 130 
#define  WT_EVENT_RENAME 129 
#define  WT_EVENT_SCAN_DIR 128 
 int /*<<< orphan*/  check_full_path_ignore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_locked_file_before_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_list_free_full (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (char*)) ; 
 TYPE_2__* g_queue_peek_head (int /*<<< orphan*/ ) ; 
 TYPE_2__* g_queue_peek_tail (int /*<<< orphan*/ ) ; 
 TYPE_2__* g_queue_pop_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_add_files (TYPE_3__*,struct index_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_rename (TYPE_3__*,struct index_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_office_lock_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  is_path_writable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_office_file_on_server (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_from_changeset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_from_index_with_prefix (struct index_state*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  scan_subtree_for_deletion (int /*<<< orphan*/ ,struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_worktree_for_changes (struct index_state*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_11__* seaf ; 
 int /*<<< orphan*/  seaf_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_filelock_manager_is_file_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_sync_manager_delete_active_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 TYPE_1__* seaf_wt_monitor_get_worktree_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_file_sync_error_notification (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_add_empty_parent_dir_entry_from_wt (int /*<<< orphan*/ ,struct index_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_office_file_on_server (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  update_attributes (TYPE_3__*,struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_path_sync_status (TYPE_3__*,TYPE_1__*,struct index_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wt_event_free (TYPE_2__*) ; 
 int /*<<< orphan*/  wt_status_unref (TYPE_1__*) ; 

__attribute__((used)) static int
apply_worktree_changes_to_index (SeafRepo *repo, struct index_state *istate,
                                 SeafileCrypt *crypt, GList *ignore_list,
                                 LockedFileSet *fset)
{
    WTStatus *status;
    WTEvent *event, *next_event;
    gboolean not_found;
#if defined WIN32 || defined __APPLE__
    char *office_path = NULL;
#endif

    status = seaf_wt_monitor_get_worktree_status (seaf->wt_monitor, repo->id);
    if (!status) {
        seaf_warning ("Can't find worktree status for repo %s(%.8s).\n",
                      repo->name, repo->id);
        return -1;
    }

    update_path_sync_status (repo, status, istate, ignore_list);

    GList *scanned_dirs = NULL, *scanned_del_dirs = NULL;

    WTEvent *last_event;

    pthread_mutex_lock (&status->q_lock);
    last_event = g_queue_peek_tail (status->event_q);
    pthread_mutex_unlock (&status->q_lock);

    if (!last_event) {
        seaf_message ("All events are processed for repo %s.\n", repo->id);
        status->partial_commit = FALSE;
        goto out;
    }

    gint64 total_size = 0;

    while (1) {
        pthread_mutex_lock (&status->q_lock);
        event = g_queue_pop_head (status->event_q);
        next_event = g_queue_peek_head (status->event_q);
        pthread_mutex_unlock (&status->q_lock);
        if (!event)
            break;

        /* Scanned dirs list is used to avoid redundant scan of consecutive
           CREATE_OR_UPDATE events. When we see other events, we should
           clear the list. Otherwise in some cases we'll get wrong result.
           For example, the following sequence (run with a script):
           1. Add a dir with files
           2. Delete the dir with files
           3. Add back the same dir again.
        */
        if (event->ev_type != WT_EVENT_CREATE_OR_UPDATE) {
            g_list_free_full (scanned_dirs, g_free);
            scanned_dirs = NULL;
        }

        switch (event->ev_type) {
        case WT_EVENT_CREATE_OR_UPDATE:
            /* If consecutive CREATE_OR_UPDATE events present
               in the event queue, only process the last one.
            */
            if (next_event &&
                next_event->ev_type == event->ev_type &&
                strcmp (next_event->path, event->path) == 0)
                break;

            /* CREATE_OR_UPDATE event tells us the exact path of changed file/dir.
             * If the event path is not writable, we don't need to check the paths
             * under the event path.
             */
            if (!is_path_writable(repo->id,
                                  repo->is_readonly, event->path)) {
                send_file_sync_error_notification (repo->id, repo->name, event->path,
                                                   SYNC_ERROR_ID_UPDATE_TO_READ_ONLY_REPO);
                seaf_debug ("%s is not writable, ignore.\n", event->path);
                break;
            }

#if defined WIN32 || defined __APPLE__
            office_path = NULL;
            if (is_office_lock_file (repo->worktree, event->path, &office_path))
                lock_office_file_on_server (repo, office_path);
            g_free (office_path);
#endif

            if (handle_add_files (repo, istate, crypt, ignore_list,
                                  fset,
                                  status, event,
                                  &scanned_dirs, &total_size))
                goto out;

            break;
        case WT_EVENT_SCAN_DIR:
            if (handle_add_files (repo, istate, crypt, ignore_list,
                                  fset,
                                  status, event,
                                  &scanned_dirs, &total_size))
                goto out;

            break;
        case WT_EVENT_DELETE:
            seaf_sync_manager_delete_active_path (seaf->sync_mgr,
                                                  repo->id,
                                                  event->path);

#if defined WIN32 || defined __APPLE__
            office_path = NULL;
            if (is_office_lock_file (repo->worktree, event->path, &office_path))
                unlock_office_file_on_server (repo, office_path);
            g_free (office_path);
#endif

            if (check_full_path_ignore(repo->worktree, event->path, ignore_list))
                break;

            if (!is_path_writable(repo->id,
                                  repo->is_readonly, event->path)) {
                seaf_debug ("%s is not writable, ignore.\n", event->path);
                break;
            }

            if (seaf_filelock_manager_is_file_locked (seaf->filelock_mgr,
                                                      repo->id, event->path)) {
                seaf_debug ("Delete: %s is locked on server, ignore.\n", event->path);
                /* send_sync_error_notification (repo->id, NULL, event->path, */
                /*                               SYNC_ERROR_ID_FILE_LOCKED); */
                break;
            }

            if (check_locked_file_before_remove (fset, event->path)) {
                not_found = FALSE;
                remove_from_index_with_prefix (istate, event->path, &not_found);
                if (not_found)
                    scan_subtree_for_deletion (repo->id,
                                               istate,
                                               repo->worktree, event->path,
                                               ignore_list, fset,
                                               repo->is_readonly,
                                               &scanned_del_dirs,
                                               repo->changeset);

                remove_from_changeset (repo->changeset,
                                       DIFF_STATUS_DELETED,
                                       event->path,
                                       FALSE,
                                       NULL);

                try_add_empty_parent_dir_entry_from_wt (repo->worktree,
                                                        istate,
                                                        ignore_list,
                                                        event->path);
            }
            break;
        case WT_EVENT_RENAME:
            handle_rename (repo, istate, crypt, ignore_list, fset, event, &scanned_del_dirs, &total_size);
            break;
        case WT_EVENT_ATTRIB:
            if (!is_path_writable(repo->id,
                                  repo->is_readonly, event->path)) {
                seaf_debug ("%s is not writable, ignore.\n", event->path);
                break;
            }
            update_attributes (repo, istate, repo->worktree, event->path);
            break;
        case WT_EVENT_OVERFLOW:
            seaf_warning ("Kernel event queue overflowed, fall back to scan.\n");
            scan_worktree_for_changes (istate, repo, crypt, ignore_list, fset);
            break;
        }

        if (event == last_event) {
            wt_event_free (event);
            seaf_message ("All events are processed for repo %s.\n", repo->id);
            status->partial_commit = FALSE;
            break;
        } else
            wt_event_free (event);
    }

out:
    wt_status_unref (status);
    string_list_free (scanned_dirs);
    string_list_free (scanned_del_dirs);

    return 0;
}