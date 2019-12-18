#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_12__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_14__ {int enc_version; char* random_key; int repo_version; char* repo_salt; char const* repo_id; scalar_t__ server_url; int /*<<< orphan*/  is_readonly; int /*<<< orphan*/  sync_wt_name; TYPE_2__* manager; } ;
struct TYPE_13__ {int /*<<< orphan*/  tasks; } ;
typedef  TYPE_2__ SeafCloneManager ;
typedef  int /*<<< orphan*/  GError ;
typedef  TYPE_3__ CloneTask ;

/* Variables and functions */
 scalar_t__ canonical_server_url (char const*) ; 
 int /*<<< orphan*/  check_http_protocol (TYPE_3__*) ; 
 int /*<<< orphan*/  clone_task_free (TYPE_3__*) ; 
 TYPE_3__* clone_task_new (char const*,char const*,char const*,char const*,char const*,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 char* g_strdup (char const*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_integer_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loads (char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char*) ; 
 char const* json_string_value (int /*<<< orphan*/ *) ; 
 scalar_t__ save_task_to_db (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 

__attribute__((used)) static char *
add_task_common (SeafCloneManager *mgr, 
                 const char *repo_id,
                 int repo_version,
                 const char *peer_id,
                 const char *repo_name,
                 const char *token,
                 const char *passwd,
                 int enc_version,
                 const char *random_key,
                 const char *worktree,
                 const char *peer_addr,
                 const char *peer_port,
                 const char *email,
                 const char *more_info,
                 gboolean sync_wt_name,
                 GError **error)
{
    CloneTask *task;

    task = clone_task_new (repo_id, peer_id, repo_name,
                           token, worktree, passwd,
                           peer_addr, peer_port, email);
    task->manager = mgr;
    task->enc_version = enc_version;
    task->random_key = g_strdup (random_key);
    task->repo_version = repo_version;
    task->sync_wt_name = sync_wt_name;
    if (more_info) {
        json_error_t jerror;
        json_t *object = NULL;

        object = json_loads (more_info, 0, &jerror);
        if (!object) {
            seaf_warning ("Failed to load more sync info from json: %s.\n", jerror.text);
            clone_task_free (task);
            return NULL;
        }
        
        json_t *integer = json_object_get (object, "is_readonly");
        task->is_readonly = json_integer_value (integer);
        json_t *string = json_object_get (object, "server_url");
        if (string)
            task->server_url = canonical_server_url (json_string_value (string));
        json_t *repo_salt = json_object_get (object, "repo_salt");
        if (repo_salt)
            task->repo_salt = g_strdup (json_string_value (repo_salt));
        json_decref (object);
    }

    if (save_task_to_db (mgr, task) < 0) {
        seaf_warning ("[Clone mgr] failed to save task.\n");
        clone_task_free (task);
        return NULL;
    }

    if (task->repo_version > 0) {
        if (task->server_url) {
            check_http_protocol (task);
        } else {
            clone_task_free (task);
            return NULL;
        }
    } 

    /* The old task for this repo will be freed. */
    g_hash_table_insert (mgr->tasks, g_strdup(task->repo_id), task);

    return g_strdup(repo_id);
}