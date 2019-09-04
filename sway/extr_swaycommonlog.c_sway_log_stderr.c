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
typedef  int /*<<< orphan*/  time_t ;
typedef  int sway_log_importance_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 int SWAY_LOG_IMPORTANCE_LAST ; 
 scalar_t__ colored ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 struct tm* localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int log_importance ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 char** verbosity_colors ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sway_log_stderr(sway_log_importance_t verbosity, const char *fmt,
		va_list args) {
	if (verbosity > log_importance) {
		return;
	}
	// prefix the time to the log message
	struct tm result;
	time_t t = time(NULL);
	struct tm *tm_info = localtime_r(&t, &result);
	char buffer[26];

	// generate time prefix
	strftime(buffer, sizeof(buffer), "%F %T - ", tm_info);
	fprintf(stderr, "%s", buffer);

	unsigned c = (verbosity < SWAY_LOG_IMPORTANCE_LAST) ? verbosity :
		SWAY_LOG_IMPORTANCE_LAST - 1;

	if (colored && isatty(STDERR_FILENO)) {
		fprintf(stderr, "%s", verbosity_colors[c]);
	}

	vfprintf(stderr, fmt, args);

	if (colored && isatty(STDERR_FILENO)) {
		fprintf(stderr, "\x1B[0m");
	}
	fprintf(stderr, "\n");
}