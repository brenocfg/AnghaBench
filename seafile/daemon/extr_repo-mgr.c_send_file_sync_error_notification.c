#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_5__ {int /*<<< orphan*/  mq_mgr; int /*<<< orphan*/  sync_mgr; int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_4__ {char* name; } ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_integer (int) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_set_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_string (char const*) ; 
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  seaf_mq_manager_publish_notification (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_1__* seaf_repo_manager_get_repo (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_repo_manager_record_sync_error (char const*,char const*,char const*,int) ; 
 int /*<<< orphan*/  seaf_sync_manager_set_task_error_code (int /*<<< orphan*/ ,char const*,int) ; 

void
send_file_sync_error_notification (const char *repo_id,
                                   const char *repo_name,
                                   const char *path,
                                   int err_id)
{
    if (!repo_name) {
        SeafRepo *repo = seaf_repo_manager_get_repo (seaf->repo_mgr, repo_id);
        if (!repo)
            return;
        repo_name = repo->name;
    }

    seaf_repo_manager_record_sync_error (repo_id, repo_name, path, err_id);

    seaf_sync_manager_set_task_error_code (seaf->sync_mgr, repo_id, err_id);

    json_t *object;
    char *str;

    object = json_object ();
    json_object_set_new (object, "repo_id", json_string(repo_id));
    json_object_set_new (object, "repo_name", json_string(repo_name));
    json_object_set_new (object, "path", json_string(path));
    json_object_set_new (object, "err_id", json_integer(err_id));

    str = json_dumps (object, 0);

    seaf_mq_manager_publish_notification (seaf->mq_mgr,
                                          "sync.error",
                                          str);

    free (str);
    json_decref (object);
}