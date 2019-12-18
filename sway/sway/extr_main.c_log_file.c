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
 int /*<<< orphan*/  SWAY_INFO ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void log_file(FILE *f) {
	char *line = NULL;
	size_t line_size = 0;
	ssize_t nread;
	while ((nread = getline(&line, &line_size, f)) != -1) {
		if (line[nread - 1] == '\n') {
			line[nread - 1] = '\0';
		}
		sway_log(SWAY_INFO, "%s", line);
	}
	free(line);
}