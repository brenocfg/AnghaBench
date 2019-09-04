#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_5__ {TYPE_1__* data; struct TYPE_5__* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  token; int /*<<< orphan*/  repo_id; } ;
typedef  TYPE_1__ HttpFolderPermReq ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int /*<<< orphan*/ * json_array () ; 
 int /*<<< orphan*/  json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_integer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_set_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

__attribute__((used)) static char *
compose_get_folder_perms_request (GList *requests)
{
    GList *ptr;
    HttpFolderPermReq *req;
    json_t *object, *array;
    char *req_str = NULL;

    array = json_array ();

    for (ptr = requests; ptr; ptr = ptr->next) {
        req = ptr->data;

        object = json_object ();
        json_object_set_new (object, "repo_id", json_string(req->repo_id));
        json_object_set_new (object, "token", json_string(req->token));
        json_object_set_new (object, "ts", json_integer(req->timestamp));

        json_array_append_new (array, object);
    }

    req_str = json_dumps (array, 0);
    if (!req_str) {
        seaf_warning ("Faile to json_dumps.\n");
    }

    json_decref (array);
    return req_str;
}