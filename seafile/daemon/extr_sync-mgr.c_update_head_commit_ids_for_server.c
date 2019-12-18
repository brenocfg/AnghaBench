#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* gpointer ;
typedef  scalar_t__ gint64 ;
struct TYPE_4__ {int /*<<< orphan*/  http_tx_mgr; int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_3__ {int http_version; int /*<<< orphan*/  head_commit_map_lock; scalar_t__ last_update_head_commit_map_time; scalar_t__ head_commit_map_init; int /*<<< orphan*/ * head_commit_map; int /*<<< orphan*/  use_fileserver_port; int /*<<< orphan*/  effective_host; } ;
typedef  TYPE_1__ HttpServerState ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  g_free ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_list_free_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * http_tx_manager_get_head_commit_ids (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* seaf ; 
 int /*<<< orphan*/  seaf_debug (char*,char*) ; 
 int /*<<< orphan*/ * seaf_repo_manager_get_repo_id_list_by_server (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
update_head_commit_ids_for_server (gpointer key, gpointer value, gpointer user_data)
{
    char *server_url = key;
    HttpServerState *state = value;

    /* Only get head commit ids from server if:
     * 1. syncing protocol version has been checked, and
     * 2. protocol version is at least 2.
     */
    if (state->http_version >= 2) {
        seaf_debug ("Updating repo head commit ids for server %s.\n", server_url);
        GList *repo_id_list = seaf_repo_manager_get_repo_id_list_by_server (seaf->repo_mgr,
                                                                            server_url);
        if (!repo_id_list) {
            return;
        }

        GHashTable *new_map = http_tx_manager_get_head_commit_ids (seaf->http_tx_mgr,
                                                                   state->effective_host,
                                                                   state->use_fileserver_port,
                                                                   repo_id_list);
        if (new_map) {
            pthread_mutex_lock (&state->head_commit_map_lock);
            g_hash_table_destroy (state->head_commit_map);
            state->head_commit_map = new_map;
            if (!state->head_commit_map_init)
                state->head_commit_map_init = TRUE;
            state->last_update_head_commit_map_time = (gint64)time(NULL);
            pthread_mutex_unlock (&state->head_commit_map_lock);
        }

        g_list_free_full (repo_id_list, g_free);
    }
}