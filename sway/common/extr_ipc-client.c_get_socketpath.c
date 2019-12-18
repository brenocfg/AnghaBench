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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 char* strdup (char const*) ; 

char *get_socketpath(void) {
	const char *swaysock = getenv("SWAYSOCK");
	if (swaysock) {
		return strdup(swaysock);
	}
	char *line = NULL;
	size_t line_size = 0;
	FILE *fp = popen("sway --get-socketpath 2>/dev/null", "r");
	if (fp) {
		ssize_t nret = getline(&line, &line_size, fp);
		pclose(fp);
		if (nret > 0) {
			// remove trailing newline, if there is one
			if (line[nret - 1] == '\n') {
				line[nret - 1] = '\0';
			}
			return line;
		}
	}
	const char *i3sock = getenv("I3SOCK");
	if (i3sock) {
		free(line);
		return strdup(i3sock);
	}
	fp = popen("i3 --get-socketpath 2>/dev/null", "r");
	if (fp) {
		ssize_t nret = getline(&line, &line_size, fp);
		pclose(fp);
		if (nret > 0) {
			// remove trailing newline, if there is one
			if (line[nret - 1] == '\n') {
				line[nret - 1] = '\0';
			}
			return line;
		}
	}
	free(line);
	return NULL;
}