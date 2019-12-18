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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DEFAULT_VERBOSITY ; 
 char* KILL_PROCESS_GROUP_GROUP_ENV_VAR ; 
 char* SUBREAPER_ENV_VAR ; 
 char* TINI_VERSION_STRING ; 
 char* VERBOSITY_ENV_VAR ; 
 char* basename (char* const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ * const,char*,...) ; 

void print_usage(char* const name, FILE* const file) {
	fprintf(file, "%s (%s)\n", basename(name), TINI_VERSION_STRING);

#if TINI_MINIMAL
	fprintf(file, "Usage: %s PROGRAM [ARGS] | --version\n\n", basename(name));
#else
	fprintf(file, "Usage: %s [OPTIONS] PROGRAM -- [ARGS] | --version\n\n", basename(name));
#endif
	fprintf(file, "Execute a program under the supervision of a valid init process (%s)\n\n", basename(name));

	fprintf(file, "Command line options:\n\n");

	fprintf(file, "  --version: Show version and exit.\n");

#if TINI_MINIMAL
#else
	fprintf(file, "  -h: Show this help message and exit.\n");
#if HAS_SUBREAPER
	fprintf(file, "  -s: Register as a process subreaper (requires Linux >= 3.4).\n");
#endif
	fprintf(file, "  -p SIGNAL: Trigger SIGNAL when parent dies, e.g. \"-p SIGKILL\".\n");
	fprintf(file, "  -v: Generate more verbose output. Repeat up to 3 times.\n");
	fprintf(file, "  -w: Print a warning when processes are getting reaped.\n");
	fprintf(file, "  -g: Send signals to the child's process group.\n");
	fprintf(file, "  -e EXIT_CODE: Remap EXIT_CODE (from 0 to 255) to 0.\n");
	fprintf(file, "  -l: Show license and exit.\n");
#endif

	fprintf(file, "\n");

	fprintf(file, "Environment variables:\n\n");
#if HAS_SUBREAPER
	fprintf(file, "  %s: Register as a process subreaper (requires Linux >= 3.4).\n", SUBREAPER_ENV_VAR);
#endif
	fprintf(file, "  %s: Set the verbosity level (default: %d).\n", VERBOSITY_ENV_VAR, DEFAULT_VERBOSITY);
	fprintf(file, "  %s: Send signals to the child's process group.\n", KILL_PROCESS_GROUP_GROUP_ENV_VAR);

	fprintf(file, "\n");
}