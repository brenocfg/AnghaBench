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
typedef  int gboolean ;
typedef  int /*<<< orphan*/  SeafRepo ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_strcmp0 (char*,char*) ; 
 int /*<<< orphan*/  seaf ; 
 char* seafile_session_config_get_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seafile_session_config_set_string (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static gboolean
need_notify_sync (SeafRepo *repo)
{
    char *notify_setting = seafile_session_config_get_string(seaf, "notify_sync");
    if (notify_setting == NULL) {
        seafile_session_config_set_string(seaf, "notify_sync", "on");
        return TRUE;
    }

    gboolean result = (g_strcmp0(notify_setting, "on") == 0);
    g_free (notify_setting);
    return result;
}