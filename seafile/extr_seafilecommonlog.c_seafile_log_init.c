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

/* Variables and functions */
 int G_LOG_FLAG_FATAL ; 
 int G_LOG_FLAG_RECURSION ; 
 int /*<<< orphan*/  G_LOG_LEVEL_DEBUG ; 
 int /*<<< orphan*/  G_LOG_LEVEL_INFO ; 
 int G_LOG_LEVEL_MASK ; 
 int /*<<< orphan*/  ccnet_expand_path (char const*) ; 
 int /*<<< orphan*/  ccnet_log ; 
 void* ccnet_log_level ; 
 int /*<<< orphan*/ * g_fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_log_set_handler (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 void* get_debug_level (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logfile ; 
 int /*<<< orphan*/ * logfp ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seafile_log ; 
 void* seafile_log_level ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char const*,char*) ; 

int
seafile_log_init (const char *_logfile, const char *ccnet_debug_level_str,
                  const char *seafile_debug_level_str)
{
    g_log_set_handler (NULL, G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL
                       | G_LOG_FLAG_RECURSION, seafile_log, NULL);
    g_log_set_handler ("Ccnet", G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL
                       | G_LOG_FLAG_RECURSION, ccnet_log, NULL);

    /* record all log message */
    ccnet_log_level = get_debug_level(ccnet_debug_level_str, G_LOG_LEVEL_INFO);
    seafile_log_level = get_debug_level(seafile_debug_level_str, G_LOG_LEVEL_DEBUG);

    if (strcmp(_logfile, "-") == 0) {
        logfp = stdout;
        logfile = g_strdup (_logfile);
    }
    else {
        logfile = ccnet_expand_path(_logfile);
        if ((logfp = g_fopen (logfile, "a+")) == NULL) {
            seaf_message ("Failed to open file %s\n", logfile);
            return -1;
        }
    }

    return 0;
}