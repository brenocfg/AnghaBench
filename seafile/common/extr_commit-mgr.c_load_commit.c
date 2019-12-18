#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_8__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;
struct TYPE_10__ {TYPE_2__* manager; } ;
struct TYPE_9__ {int /*<<< orphan*/  obj_store; } ;
typedef  TYPE_2__ SeafCommitManager ;
typedef  TYPE_3__ SeafCommit ;

/* Variables and functions */
 int /*<<< orphan*/  clean_utf8_data (char*,int) ; 
 TYPE_3__* commit_from_json_object (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loadb (char*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ seaf_obj_store_read_obj (int /*<<< orphan*/ ,char const*,int,char const*,void**,int*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static SeafCommit *
load_commit (SeafCommitManager *mgr,
             const char *repo_id,
             int version,
             const char *commit_id)
{
    char *data = NULL;
    int len;
    SeafCommit *commit = NULL;
    json_t *object = NULL;
    json_error_t jerror;

    if (!commit_id || strlen(commit_id) != 40)
        return NULL;

    if (seaf_obj_store_read_obj (mgr->obj_store, repo_id, version,
                                 commit_id, (void **)&data, &len) < 0)
        return NULL;

    object = json_loadb (data, len, 0, &jerror);
    if (!object) {
        /* Perhaps the commit object contains invalid UTF-8 character. */
        if (data[len-1] == 0)
            clean_utf8_data (data, len - 1);
        else
            clean_utf8_data (data, len);

        object = json_loadb (data, len, 0, &jerror);
        if (!object) {
            seaf_warning ("Failed to load commit json object: %s.\n", jerror.text);
            goto out;
        }
    }

    commit = commit_from_json_object (commit_id, object);
    if (commit)
        commit->manager = mgr;

out:
    if (object) json_decref (object);
    g_free (data);

    return commit;
}