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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  SeafileEncryptionInfo ;
typedef  int /*<<< orphan*/  GObject ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAFILE_TYPE_ENCRYPTION_INFO ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_ARGS ; 
 int /*<<< orphan*/ * g_object_new (int /*<<< orphan*/ ,char*,char const*,char*,char const*,char*,int,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seafile_generate_magic (int,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ seafile_generate_random_key (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ seafile_generate_repo_salt (int /*<<< orphan*/ *) ; 

GObject *
seafile_generate_magic_and_random_key(int enc_version,
                                      const char* repo_id,
                                      const char *passwd,
                                      GError **error)
{
    if (!repo_id || !passwd) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Argument should not be null");
        return NULL;
    }

    gchar salt[65] = {0};
    gchar magic[65] = {0};
    gchar random_key[97] = {0};

    if (enc_version >= 3 && seafile_generate_repo_salt (salt) < 0) {
        return NULL;
    }

    seafile_generate_magic (enc_version, repo_id, passwd, salt, magic);
    if (seafile_generate_random_key (passwd, enc_version, salt, random_key) < 0) {
        return NULL;
    }
    
    SeafileEncryptionInfo *sinfo;
    sinfo = g_object_new (SEAFILE_TYPE_ENCRYPTION_INFO,
                          "repo_id", repo_id,
                          "passwd", passwd,
                          "enc_version", enc_version,
                          "magic", magic,
                          "random_key", random_key,
                          NULL);

    if (enc_version >= 3)
        g_object_set (sinfo, "salt", salt, NULL);

    return (GObject *)sinfo;

}