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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int time_t ;
struct skynet_context {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* ctime (int*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  skynet_error (struct skynet_context*,char*,char*) ; 
 char* skynet_getenv (char*) ; 
 int skynet_now () ; 
 int skynet_starttime () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,int) ; 
 size_t strlen (char const*) ; 

FILE * 
skynet_log_open(struct skynet_context * ctx, uint32_t handle) {
	const char * logpath = skynet_getenv("logpath");
	if (logpath == NULL)
		return NULL;
	size_t sz = strlen(logpath);
	char tmp[sz + 16];
	sprintf(tmp, "%s/%08x.log", logpath, handle);
	FILE *f = fopen(tmp, "ab");
	if (f) {
		uint32_t starttime = skynet_starttime();
		uint64_t currenttime = skynet_now();
		time_t ti = starttime + currenttime/100;
		skynet_error(ctx, "Open log file %s", tmp);
		fprintf(f, "open time: %u %s", (uint32_t)currenttime, ctime(&ti));
		fflush(f);
	} else {
		skynet_error(ctx, "Open log file %s fail", tmp);
	}
	return f;
}