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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  gpointer ;
typedef  char gchar ;
typedef  scalar_t__ GLogLevelFlags ;

/* Variables and functions */
 scalar_t__ enable_syslog ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_return_if_fail (int) ; 
 int /*<<< orphan*/  get_syslog_level (scalar_t__) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * logfp ; 
 int /*<<< orphan*/  printf (char*,char*,char const*) ; 
 scalar_t__ seafile_log_level ; 
 int strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void 
seafile_log (const gchar *log_domain, GLogLevelFlags log_level,
             const gchar *message,    gpointer user_data)
{
    time_t t;
    struct tm *tm;
    char buf[1024];
    int len;

    if (log_level > seafile_log_level)
        return;

    t = time(NULL);
    tm = localtime(&t);
    len = strftime (buf, 1024, "[%x %X] ", tm);
    g_return_if_fail (len < 1024);
    if (logfp != NULL) {    
        fputs (buf, logfp);
        fputs (message, logfp);
        fflush (logfp);
    } else { // log file not available
        printf("%s %s", buf, message);
    }

#ifndef WIN32
#ifdef SEAFILE_SERVER
    if (enable_syslog)
        syslog (get_syslog_level (log_level), "%s", message);
#endif
#endif
}