#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  GKeyFile ;
typedef  TYPE_1__ GError ;

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_TEST_IS_REGULAR ; 
 char* g_build_path (char*,char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_clear_error (TYPE_1__**) ; 
 int /*<<< orphan*/  g_file_test (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_key_file_free (int /*<<< orphan*/ *) ; 
 char* g_key_file_get_string (int /*<<< orphan*/ *,char*,char*,TYPE_1__**) ; 
 int /*<<< orphan*/  g_key_file_load_from_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/ * g_key_file_new () ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
read_ccnet_conf (const char *ccnet_dir, char **client_id, char **client_name)
{
    char *ccnet_conf_path = g_build_path ("/", ccnet_dir, "ccnet.conf", NULL);
    GKeyFile *key_file = g_key_file_new ();
    GError *error = NULL;

    if (!g_file_test (ccnet_conf_path, G_FILE_TEST_IS_REGULAR))
        goto out;

    if (!g_key_file_load_from_file (key_file, ccnet_conf_path, 0, &error)) {
        seaf_warning ("Failed to read ccnet.conf: %s.\n", error->message);
        g_clear_error (&error);
        goto out;
    }

    *client_id = g_key_file_get_string (key_file, "General", "ID", &error);
    if (error) {
        seaf_warning ("Failed to read client id from ccnet.conf: %s.\n", error->message);
        g_clear_error (&error);
        goto out;
    }

    *client_name = g_key_file_get_string (key_file, "General", "NAME", &error);
    if (error) {
        seaf_warning ("Failed to read client name from ccnet.conf: %s.\n", error->message);
        g_clear_error (&error);
        goto out;
    }

out:
    g_free (ccnet_conf_path);
    g_key_file_free (key_file);
}