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
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 char* realloc (char*,size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static ssize_t getline_with_cont(char **lineptr, size_t *line_size, FILE *file,
		int *nlines) {
	char *next_line = NULL;
	size_t next_line_size = 0;
	ssize_t nread = getline(lineptr, line_size, file);
	*nlines = nread == -1 ? 0 : 1;
	while (nread >= 2 && strcmp(&(*lineptr)[nread - 2], "\\\n") == 0 && (*lineptr)[0] != '#') {
		ssize_t next_nread = getline(&next_line, &next_line_size, file);
		if (next_nread == -1) {
			break;
		}
		(*nlines)++;

		nread += next_nread - 2;
		if ((ssize_t) *line_size < nread + 1) {
			*line_size = nread + 1;
			char *old_ptr = *lineptr;
			*lineptr = realloc(*lineptr, *line_size);
			if (!*lineptr) {
				free(old_ptr);
				nread = -1;
				break;
			}
		}
		strcpy(&(*lineptr)[nread - next_nread], next_line);
	}
	free(next_line);
	return nread;
}