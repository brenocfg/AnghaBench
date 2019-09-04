#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tm {int dummy; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {char* logfile; int verbosity; scalar_t__ pid; scalar_t__ syslog_enabled; scalar_t__ masterhost; scalar_t__ sentinel_mode; int /*<<< orphan*/  daylight_active; int /*<<< orphan*/  timezone; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LL_RAW ; 
 int const LOG_DEBUG ; 
 int const LOG_INFO ; 
 int const LOG_NOTICE ; 
 int const LOG_WARNING ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nolocks_localtime (struct tm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/ * stdout ; 
 int strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  syslog (int const,char*,char const*) ; 

void serverLogRaw(int level, const char *msg) {
    const int syslogLevelMap[] = { LOG_DEBUG, LOG_INFO, LOG_NOTICE, LOG_WARNING };
    const char *c = ".-*#";
    FILE *fp;
    char buf[64];
    int rawmode = (level & LL_RAW);
    int log_to_stdout = server.logfile[0] == '\0';

    level &= 0xff; /* clear flags */
    if (level < server.verbosity) return;

    fp = log_to_stdout ? stdout : fopen(server.logfile,"a");
    if (!fp) return;

    if (rawmode) {
        fprintf(fp,"%s",msg);
    } else {
        int off;
        struct timeval tv;
        int role_char;
        pid_t pid = getpid();

        gettimeofday(&tv,NULL);
        struct tm tm;
        nolocks_localtime(&tm,tv.tv_sec,server.timezone,server.daylight_active);
        off = strftime(buf,sizeof(buf),"%d %b %Y %H:%M:%S.",&tm);
        snprintf(buf+off,sizeof(buf)-off,"%03d",(int)tv.tv_usec/1000);
        if (server.sentinel_mode) {
            role_char = 'X'; /* Sentinel. */
        } else if (pid != server.pid) {
            role_char = 'C'; /* RDB / AOF writing child. */
        } else {
            role_char = (server.masterhost ? 'S':'M'); /* Slave or Master. */
        }
        fprintf(fp,"%d:%c %s %c %s\n",
            (int)getpid(),role_char, buf,c[level],msg);
    }
    fflush(fp);

    if (!log_to_stdout) fclose(fp);
    if (server.syslog_enabled) syslog(syslogLevelMap[level], "%s", msg);
}