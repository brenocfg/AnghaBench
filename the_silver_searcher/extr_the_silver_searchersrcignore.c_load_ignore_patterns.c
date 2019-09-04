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
typedef  int /*<<< orphan*/  ignores ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  add_ignore_pattern (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 

void load_ignore_patterns(ignores *ig, const char *path) {
    FILE *fp = NULL;
    fp = fopen(path, "r");
    if (fp == NULL) {
        log_debug("Skipping ignore file %s: not readable", path);
        return;
    }
    log_debug("Loading ignore file %s.", path);

    char *line = NULL;
    ssize_t line_len = 0;
    size_t line_cap = 0;

    while ((line_len = getline(&line, &line_cap, fp)) > 0) {
        if (line_len == 0 || line[0] == '\n' || line[0] == '#') {
            continue;
        }
        if (line[line_len - 1] == '\n') {
            line[line_len - 1] = '\0'; /* kill the \n */
        }
        add_ignore_pattern(ig, line);
    }

    free(line);
    fclose(fp);
}