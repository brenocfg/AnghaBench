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
typedef  int /*<<< orphan*/  va_list ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int VIS_CSTYLE ; 
 int VIS_NL ; 
 int VIS_OCTAL ; 
 int VIS_TAB ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int fprintf (int /*<<< orphan*/ *,char*,long long,int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * log_file ; 
 int stravis (char**,char*,int) ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
log_vwrite(const char *msg, va_list ap)
{
	char		*fmt, *out;
	struct timeval	 tv;

	if (log_file == NULL)
		return;

	if (vasprintf(&fmt, msg, ap) == -1)
		exit(1);
	if (stravis(&out, fmt, VIS_OCTAL|VIS_CSTYLE|VIS_TAB|VIS_NL) == -1)
		exit(1);

	gettimeofday(&tv, NULL);
	if (fprintf(log_file, "%lld.%06d %s\n", (long long)tv.tv_sec,
	    (int)tv.tv_usec, out) == -1)
		exit(1);
	fflush(log_file);

	free(out);
	free(fmt);
}