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
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strip_whitespace (char*) ; 

__attribute__((used)) static int detect_brace(FILE *file) {
	int ret = 0;
	int lines = 0;
	long pos = ftell(file);
	char *line = NULL;
	size_t line_size = 0;
	while ((getline(&line, &line_size, file)) != -1) {
		lines++;
		strip_whitespace(line);
		if (*line) {
			if (strcmp(line, "{") == 0) {
				ret = lines;
			}
			break;
		}
	}
	free(line);
	if (ret == 0) {
		fseek(file, pos, SEEK_SET);
	}
	return ret;
}