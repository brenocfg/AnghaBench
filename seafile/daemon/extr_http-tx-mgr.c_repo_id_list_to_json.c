#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_3__ {char* data; struct TYPE_3__* next; } ;
typedef  TYPE_1__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_COMPACT ; 
 int /*<<< orphan*/ * json_array () ; 
 int /*<<< orphan*/  json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_string (char*) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

__attribute__((used)) static char *
repo_id_list_to_json (GList *repo_id_list)
{
    json_t *array = json_array();
    GList *ptr;
    char *repo_id;

    for (ptr = repo_id_list; ptr; ptr = ptr->next) {
        repo_id = ptr->data;
        json_array_append_new (array, json_string(repo_id));
    }

    char *data = json_dumps (array, JSON_COMPACT);
    if (!data) {
        seaf_warning ("Failed to dump json.\n");
        json_decref (array);
        return NULL;
    }

    json_decref (array);
    return data;
}