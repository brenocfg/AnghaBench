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
typedef  int gint64 ;
struct TYPE_3__ {char* commit_id; char* root_id; char* repo_id; char* creator_name; char* creator_id; char* desc; char* repo_name; char* repo_desc; char* device_name; char* client_version; int enc_version; char* magic; char* random_key; char* salt; int version; scalar_t__ repaired; scalar_t__ new_merge; scalar_t__ conflict; scalar_t__ no_local_history; scalar_t__ encrypted; int /*<<< orphan*/  repo_category; int /*<<< orphan*/  second_parent_id; int /*<<< orphan*/  parent_id; scalar_t__ ctime; } ;
typedef  TYPE_1__ SeafCommit ;

/* Variables and functions */
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_set_int_member (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  json_object_set_string_member (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  json_object_set_string_or_null_member (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static json_t *
commit_to_json_object (SeafCommit *commit)
{
    json_t *object;
    
    object = json_object ();
 
    json_object_set_string_member (object, "commit_id", commit->commit_id);
    json_object_set_string_member (object, "root_id", commit->root_id);
    json_object_set_string_member (object, "repo_id", commit->repo_id);
    if (commit->creator_name)
        json_object_set_string_member (object, "creator_name", commit->creator_name);
    json_object_set_string_member (object, "creator", commit->creator_id);
    json_object_set_string_member (object, "description", commit->desc);
    json_object_set_int_member (object, "ctime", (gint64)commit->ctime);
    json_object_set_string_or_null_member (object, "parent_id", commit->parent_id);
    json_object_set_string_or_null_member (object, "second_parent_id",
                                           commit->second_parent_id);
    /*
     * also save repo's properties to commit file, for easy sharing of
     * repo info 
     */
    json_object_set_string_member (object, "repo_name", commit->repo_name);
    json_object_set_string_member (object, "repo_desc",
                                   commit->repo_desc);
    json_object_set_string_or_null_member (object, "repo_category",
                                           commit->repo_category);
    if (commit->device_name)
        json_object_set_string_member (object, "device_name", commit->device_name);

    if (commit->client_version)
        json_object_set_string_member (object, "client_version", commit->client_version);

    if (commit->encrypted)
        json_object_set_string_member (object, "encrypted", "true");

    if (commit->encrypted) {
        json_object_set_int_member (object, "enc_version", commit->enc_version);
        if (commit->enc_version >= 1)
            json_object_set_string_member (object, "magic", commit->magic);
        if (commit->enc_version >= 2)
            json_object_set_string_member (object, "key", commit->random_key);
        if (commit->enc_version >= 3)
            json_object_set_string_member (object, "salt", commit->salt);
    }
    if (commit->no_local_history)
        json_object_set_int_member (object, "no_local_history", 1);
    if (commit->version != 0)
        json_object_set_int_member (object, "version", commit->version);
    if (commit->conflict)
        json_object_set_int_member (object, "conflict", 1);
    if (commit->new_merge)
        json_object_set_int_member (object, "new_merge", 1);
    if (commit->repaired)
        json_object_set_int_member (object, "repaired", 1);

    return object;
}