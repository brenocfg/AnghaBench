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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {int /*<<< orphan*/  config_db; } ;
typedef  TYPE_1__ SeafileSession ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int atoi (char*) ; 
 char* config_get_string (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  g_free (char*) ; 

int
seafile_session_config_get_int (SeafileSession *session,
                                const char *key,
                                gboolean *exists)
{
    char *value;
    int ret;

    value = config_get_string (session->config_db, key);
    if (!value) {
        if (exists)
            *exists = FALSE;
        return -1;
    }

    if (exists)
        *exists = TRUE;
    ret = atoi (value);
    g_free (value);
    return ret;
}