#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const** names; size_t names_len; int abs_path_len; char const** slash_names; size_t slash_names_len; size_t slash_regexes_len; char const** slash_regexes; size_t invert_regexes_len; char const** invert_regexes; size_t regexes_len; char const** regexes; int /*<<< orphan*/  abs_path; } ;
typedef  TYPE_1__ ignores ;

/* Variables and functions */
 int ackmate_dir_match (char*) ; 
 int /*<<< orphan*/  ag_asprintf (char**,char*,char const*,char const*) ; 
 int binary_search (char const*,char const**,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ fnmatch (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnmatch_flags ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_debug (char*,char const*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 char* strstr (char*,char const*) ; 

__attribute__((used)) static int path_ignore_search(const ignores *ig, const char *path, const char *filename) {
    char *temp;
    size_t i;
    int match_pos;

    match_pos = binary_search(filename, ig->names, 0, ig->names_len);
    if (match_pos >= 0) {
        log_debug("file %s ignored because name matches static pattern %s", filename, ig->names[match_pos]);
        return 1;
    }

    ag_asprintf(&temp, "%s/%s", path[0] == '.' ? path + 1 : path, filename);

    if (strncmp(temp, ig->abs_path, ig->abs_path_len) == 0) {
        char *slash_filename = temp + ig->abs_path_len;
        if (slash_filename[0] == '/') {
            slash_filename++;
        }
        match_pos = binary_search(slash_filename, ig->names, 0, ig->names_len);
        if (match_pos >= 0) {
            log_debug("file %s ignored because name matches static pattern %s", temp, ig->names[match_pos]);
            free(temp);
            return 1;
        }

        match_pos = binary_search(slash_filename, ig->slash_names, 0, ig->slash_names_len);
        if (match_pos >= 0) {
            log_debug("file %s ignored because name matches slash static pattern %s", slash_filename, ig->slash_names[match_pos]);
            free(temp);
            return 1;
        }

        for (i = 0; i < ig->names_len; i++) {
            char *pos = strstr(slash_filename, ig->names[i]);
            if (pos == slash_filename || (pos && *(pos - 1) == '/')) {
                pos += strlen(ig->names[i]);
                if (*pos == '\0' || *pos == '/') {
                    log_debug("file %s ignored because path somewhere matches name %s", slash_filename, ig->names[i]);
                    free(temp);
                    return 1;
                }
            }
            log_debug("pattern %s doesn't match path %s", ig->names[i], slash_filename);
        }

        for (i = 0; i < ig->slash_regexes_len; i++) {
            if (fnmatch(ig->slash_regexes[i], slash_filename, fnmatch_flags) == 0) {
                log_debug("file %s ignored because name matches slash regex pattern %s", slash_filename, ig->slash_regexes[i]);
                free(temp);
                return 1;
            }
            log_debug("pattern %s doesn't match slash file %s", ig->slash_regexes[i], slash_filename);
        }
    }

    for (i = 0; i < ig->invert_regexes_len; i++) {
        if (fnmatch(ig->invert_regexes[i], filename, fnmatch_flags) == 0) {
            log_debug("file %s not ignored because name matches regex pattern !%s", filename, ig->invert_regexes[i]);
            free(temp);
            return 0;
        }
        log_debug("pattern !%s doesn't match file %s", ig->invert_regexes[i], filename);
    }

    for (i = 0; i < ig->regexes_len; i++) {
        if (fnmatch(ig->regexes[i], filename, fnmatch_flags) == 0) {
            log_debug("file %s ignored because name matches regex pattern %s", filename, ig->regexes[i]);
            free(temp);
            return 1;
        }
        log_debug("pattern %s doesn't match file %s", ig->regexes[i], filename);
    }

    int rv = ackmate_dir_match(temp);
    free(temp);
    return rv;
}