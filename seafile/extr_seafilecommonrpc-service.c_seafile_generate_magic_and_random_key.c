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
 int /*<<< orphan*/  CURRENT_ENC_VERSION ; 
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAFILE_TYPE_ENCRYPTION_INFO ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_ARGS ; 
 int /*<<< orphan*/ * g_object_new (int /*<<< orphan*/ ,char*,char const*,char*,char const*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seafile_generate_magic (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seafile_generate_random_key (char const*,int /*<<< orphan*/ *) ; 

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

    gchar magic[65] = {0};
    gchar random_key[97] = {0};

    seafile_generate_magic (CURRENT_ENC_VERSION, repo_id, passwd, magic);
    seafile_generate_random_key (passwd, random_key);

    SeafileEncryptionInfo *sinfo;
    sinfo = g_object_new (SEAFILE_TYPE_ENCRYPTION_INFO,
                          "repo_id", repo_id,
                          "passwd", passwd,
                          "enc_version", CURRENT_ENC_VERSION,
                          "magic", magic,
                          "random_key", random_key,
                          NULL);

    return (GObject *)sinfo;

}