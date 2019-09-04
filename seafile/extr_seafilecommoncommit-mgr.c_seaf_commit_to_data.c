#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  SeafCommit ;

/* Variables and functions */
 int /*<<< orphan*/ * commit_to_json_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* g_strdup (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

char *
seaf_commit_to_data (SeafCommit *commit, gsize *len)
{
    json_t *object;
    char *json_data;
    char *ret;

    object = commit_to_json_object (commit);

    json_data = json_dumps (object, 0);
    *len = strlen (json_data);
    json_decref (object);

    ret = g_strdup (json_data);
    free (json_data);
    return ret;
}