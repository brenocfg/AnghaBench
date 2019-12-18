#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
typedef  scalar_t__ guint64 ;
typedef  scalar_t__ gint64 ;
struct TYPE_4__ {int enc_version; int version; void* repaired; void* conflict; void* new_merge; void* no_local_history; int /*<<< orphan*/ * salt; int /*<<< orphan*/ * random_key; int /*<<< orphan*/ * magic; void* encrypted; int /*<<< orphan*/ * client_version; int /*<<< orphan*/ * device_name; int /*<<< orphan*/ * repo_category; int /*<<< orphan*/ * repo_desc; int /*<<< orphan*/ * repo_name; int /*<<< orphan*/ * second_parent_id; int /*<<< orphan*/ * parent_id; } ;
typedef  TYPE_1__ SeafCommit ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 char* g_ascii_strdown (char const*,int) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/ * g_strdup (char const*) ; 
 int /*<<< orphan*/  is_object_id_valid (char const*) ; 
 int /*<<< orphan*/  is_uuid_valid (char const*) ; 
 int json_object_get_int_member (int /*<<< orphan*/ *,char*) ; 
 char* json_object_get_string_member (int /*<<< orphan*/ *,char*) ; 
 char* json_object_get_string_or_null_member (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ json_object_has_member (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* seaf_commit_new (char const*,char const*,char const*,char*,char const*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  seaf_warning (char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static SeafCommit *
commit_from_json_object (const char *commit_id, json_t *object)
{
    SeafCommit *commit = NULL;
    const char *root_id;
    const char *repo_id;
    const char *creator_name = NULL;
    const char *creator;
    const char *desc;
    gint64 ctime;
    const char *parent_id, *second_parent_id;
    const char *repo_name;
    const char *repo_desc;
    const char *repo_category;
    const char *device_name;
    const char *client_version;
    const char *encrypted = NULL;
    int enc_version = 0;
    const char *magic = NULL;
    const char *random_key = NULL;
    const char *salt = NULL;
    int no_local_history = 0;
    int version = 0;
    int conflict = 0, new_merge = 0;
    int repaired = 0;

    root_id = json_object_get_string_member (object, "root_id");
    repo_id = json_object_get_string_member (object, "repo_id");
    if (json_object_has_member (object, "creator_name"))
        creator_name = json_object_get_string_or_null_member (object, "creator_name");
    creator = json_object_get_string_member (object, "creator");
    desc = json_object_get_string_member (object, "description");
    if (!desc)
        desc = "";
    ctime = (guint64) json_object_get_int_member (object, "ctime");
    parent_id = json_object_get_string_or_null_member (object, "parent_id");
    second_parent_id = json_object_get_string_or_null_member (object, "second_parent_id");

    repo_name = json_object_get_string_member (object, "repo_name");
    if (!repo_name)
        repo_name = "";
    repo_desc = json_object_get_string_member (object, "repo_desc");
    if (!repo_desc)
        repo_desc = "";
    repo_category = json_object_get_string_or_null_member (object, "repo_category");
    device_name = json_object_get_string_or_null_member (object, "device_name");
    client_version = json_object_get_string_or_null_member (object, "client_version");

    if (json_object_has_member (object, "encrypted"))
        encrypted = json_object_get_string_or_null_member (object, "encrypted");

    if (encrypted && strcmp(encrypted, "true") == 0
        && json_object_has_member (object, "enc_version")) {
        enc_version = json_object_get_int_member (object, "enc_version");
        magic = json_object_get_string_member (object, "magic");
    }

    if (enc_version >= 2)
        random_key = json_object_get_string_member (object, "key");
    if (enc_version >= 3)
        salt = json_object_get_string_member (object, "salt");

    if (json_object_has_member (object, "no_local_history"))
        no_local_history = json_object_get_int_member (object, "no_local_history");

    if (json_object_has_member (object, "version"))
        version = json_object_get_int_member (object, "version");
    if (json_object_has_member (object, "new_merge"))
        new_merge = json_object_get_int_member (object, "new_merge");

    if (json_object_has_member (object, "conflict"))
        conflict = json_object_get_int_member (object, "conflict");

    if (json_object_has_member (object, "repaired"))
        repaired = json_object_get_int_member (object, "repaired");


    /* sanity check for incoming values. */
    if (!repo_id || !is_uuid_valid(repo_id)  ||
        !root_id || !is_object_id_valid(root_id) ||
        !creator || strlen(creator) != 40 ||
        (parent_id && !is_object_id_valid(parent_id)) ||
        (second_parent_id && !is_object_id_valid(second_parent_id)))
        return commit;

    switch (enc_version) {
    case 0:
        break;
    case 1:
        if (!magic || strlen(magic) != 32)
            return NULL;
        break;
    case 2:
        if (!magic || strlen(magic) != 64)
            return NULL;
        if (!random_key || strlen(random_key) != 96)
            return NULL;
        break;
    case 3:
        if (!magic || strlen(magic) != 64)
            return NULL;
        if (!random_key || strlen(random_key) != 96)
            return NULL;
        if (!salt || strlen(salt) != 64)
            return NULL;
        break;
    default:
        seaf_warning ("Unknown encryption version %d.\n", enc_version);
        return NULL;
    }

    char *creator_name_l = creator_name ? g_ascii_strdown (creator_name, -1) : NULL;
    commit = seaf_commit_new (commit_id, repo_id, root_id,
                              creator_name_l, creator, desc, ctime);
    g_free (creator_name_l);

    commit->parent_id = parent_id ? g_strdup(parent_id) : NULL;
    commit->second_parent_id = second_parent_id ? g_strdup(second_parent_id) : NULL;

    commit->repo_name = g_strdup(repo_name);
    commit->repo_desc = g_strdup(repo_desc);
    if (encrypted && strcmp(encrypted, "true") == 0)
        commit->encrypted = TRUE;
    else
        commit->encrypted = FALSE;
    if (repo_category)
        commit->repo_category = g_strdup(repo_category);
    commit->device_name = g_strdup(device_name);
    commit->client_version = g_strdup(client_version);

    if (commit->encrypted) {
        commit->enc_version = enc_version;
        if (enc_version >= 1)
            commit->magic = g_strdup(magic);
        if (enc_version >= 2)
            commit->random_key = g_strdup (random_key);
        if (enc_version >= 3)
            commit->salt = g_strdup(salt);
    }
    if (no_local_history)
        commit->no_local_history = TRUE;
    commit->version = version;
    if (new_merge)
        commit->new_merge = TRUE;
    if (conflict)
        commit->conflict = TRUE;
    if (repaired)
        commit->repaired = TRUE;

    return commit;
}