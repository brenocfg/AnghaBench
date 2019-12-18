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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 char** realloc (char**,int) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
libzfs_read_stdout_from_fd(int fd, char **lines[])
{

	FILE *fp;
	int lines_cnt = 0;
	size_t len = 0;
	char *line = NULL;
	char **tmp_lines = NULL, **tmp;
	char *nl = NULL;
	int rc;

	fp = fdopen(fd, "r");
	if (fp == NULL)
		return (0);
	while (1) {
		rc = getline(&line, &len, fp);
		if (rc == -1)
			break;

		tmp = realloc(tmp_lines, sizeof (*tmp_lines) * (lines_cnt + 1));
		if (tmp == NULL) {
			/* Return the lines we were able to process */
			break;
		}
		tmp_lines = tmp;

		/* Terminate newlines */
		if ((nl = strchr(line, '\n')) != NULL)
			*nl = '\0';
		tmp_lines[lines_cnt] = line;
		lines_cnt++;
		line = NULL;
	}
	fclose(fp);
	*lines = tmp_lines;
	return (lines_cnt);
}