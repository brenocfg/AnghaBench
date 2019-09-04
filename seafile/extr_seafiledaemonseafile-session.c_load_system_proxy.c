#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_6__ {char const* text; } ;
typedef  TYPE_1__ json_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  seaf_dir; } ;
struct TYPE_7__ {void* http_proxy_password; void* http_proxy_username; int /*<<< orphan*/  http_proxy_port; void* http_proxy_addr; void* http_proxy_type; } ;
typedef  TYPE_2__ SeafileSession ;

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_TEST_EXISTS ; 
 char* g_build_filename (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_file_test (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_strcmp0 (char const*,char*) ; 
 void* g_strdup (char const*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_load_file (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  json_object_get_int_member (int /*<<< orphan*/ *,char*) ; 
 char const* json_object_get_string_member (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
load_system_proxy (SeafileSession *session)
{
    char *system_proxy_txt = g_build_filename (seaf->seaf_dir, "system-proxy.txt", NULL);
    json_t *json = NULL;
    if (!g_file_test (system_proxy_txt, G_FILE_TEST_EXISTS)) {
        seaf_warning ("Can't load system proxy: file %s doesn't exist\n", system_proxy_txt);
        goto out;
    }

    json_error_t jerror;
    json = json_load_file(system_proxy_txt, 0, &jerror);
    if (!json) {
        if (strlen(jerror.text) > 0)
            seaf_warning ("Failed to load system proxy information: %s.\n", jerror.text);
        else
            seaf_warning ("Failed to load system proxy information\n");
        goto out;
    }
    const char *type;
    type = json_object_get_string_member (json, "type");
    if (!type) {
        seaf_warning ("Failed to load system proxy information: proxy type missing\n");
        goto out;
    }
    if (strcmp(type, "none") != 0 && strcmp(type, "socks") != 0 && strcmp(type, "http") != 0) {
        seaf_warning ("Failed to load system proxy information: invalid proxy type %s\n", type);
        goto out;
    }
    if (g_strcmp0(type, "none") == 0) {
        goto out;
    }
    session->http_proxy_type = g_strdup(type);
    session->http_proxy_addr = g_strdup(json_object_get_string_member (json, "addr"));
    session->http_proxy_port = json_object_get_int_member (json, "port");
    session->http_proxy_username = g_strdup(json_object_get_string_member (json, "username"));
    session->http_proxy_password = g_strdup(json_object_get_string_member (json, "password"));

out:
    g_free (system_proxy_txt);
    if (json)
        json_decref(json);
}