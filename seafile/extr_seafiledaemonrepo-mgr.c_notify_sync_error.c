#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_9__ {int /*<<< orphan*/  mq_mgr; } ;
struct TYPE_8__ {TYPE_1__* data; } ;
struct TYPE_7__ {struct TYPE_7__* path; struct TYPE_7__* repo_name; struct TYPE_7__* repo_id; int /*<<< orphan*/  err_id; } ;
typedef  TYPE_1__ SyncErrorData ;
typedef  TYPE_2__ CEvent ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_integer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_set_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_string (TYPE_1__*) ; 
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  seaf_mq_manager_publish_notification (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
notify_sync_error (CEvent *event, void *handler_data)
{
    SyncErrorData *data = event->data;
    json_t *object;
    char *str;

    object = json_object ();
    json_object_set_new (object, "repo_id", json_string(data->repo_id));
    json_object_set_new (object, "repo_name", json_string(data->repo_name));
    json_object_set_new (object, "path", json_string(data->path));
    json_object_set_new (object, "err_id", json_integer(data->err_id));

    str = json_dumps (object, 0);

    seaf_mq_manager_publish_notification (seaf->mq_mgr,
                                          "sync.error",
                                          str);

    free (str);
    json_decref (object);
    g_free (data->repo_id);
    g_free (data->repo_name);
    g_free (data->path);
    g_free (data);
}