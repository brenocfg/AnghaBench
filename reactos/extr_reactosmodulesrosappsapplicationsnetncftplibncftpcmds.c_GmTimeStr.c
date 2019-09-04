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
struct tm {int tm_year; int tm_mon; int tm_mday; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; } ;

/* Variables and functions */
 int /*<<< orphan*/  Strncpy (char* const,char*,size_t const) ; 
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
GmTimeStr(char *const dst, const size_t dstsize, time_t t)
{
	char buf[64];
	struct tm *gtp;

	gtp = gmtime(&t);
	if (gtp == NULL) {
		dst[0] = '\0';
	} else {
#ifdef HAVE_SNPRINTF
		buf[sizeof(buf) - 1] = '\0';
		(void) snprintf(buf, sizeof(buf) - 1, "%04d%02d%02d%02d%02d%02d",
#else
		(void) sprintf(buf, "%04d%02d%02d%02d%02d%02d",
#endif
			gtp->tm_year + 1900,
			gtp->tm_mon + 1,
			gtp->tm_mday,
			gtp->tm_hour,
			gtp->tm_min,
			gtp->tm_sec
		);
		(void) Strncpy(dst, buf, dstsize);
	}
}