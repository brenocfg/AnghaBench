#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char** extensions; size_t extensions_len; char** slash_regexes; size_t slash_regexes_len; char** invert_regexes; size_t invert_regexes_len; char** regexes; size_t regexes_len; char** slash_names; size_t slash_names_len; char** names; size_t names_len; char* abs_path; } ;
typedef  TYPE_1__ ignores ;

/* Variables and functions */
 char** ag_realloc (char**,size_t) ; 
 char* ag_strndup (char const*,int) ; 
 scalar_t__ is_fnmatch (char const*) ; 
 int /*<<< orphan*/  isspace (char const) ; 
 int /*<<< orphan*/  log_debug (char*,...) ; 
 TYPE_1__* root_ignores ; 
 scalar_t__ strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

void add_ignore_pattern(ignores *ig, const char *pattern) {
    int i;
    int pattern_len;

    /* Strip off the leading dot so that matches are more likely. */
    if (strncmp(pattern, "./", 2) == 0) {
        pattern++;
    }

    /* Kill trailing whitespace */
    for (pattern_len = strlen(pattern); pattern_len > 0; pattern_len--) {
        if (!isspace(pattern[pattern_len - 1])) {
            break;
        }
    }

    if (pattern_len == 0) {
        log_debug("Pattern is empty. Not adding any ignores.");
        return;
    }

    char ***patterns_p;
    size_t *patterns_len;
    if (is_fnmatch(pattern)) {
        if (pattern[0] == '*' && pattern[1] == '.' && strchr(pattern + 2, '.') && !is_fnmatch(pattern + 2)) {
            patterns_p = &(ig->extensions);
            patterns_len = &(ig->extensions_len);
            pattern += 2;
            pattern_len -= 2;
        } else if (pattern[0] == '/') {
            patterns_p = &(ig->slash_regexes);
            patterns_len = &(ig->slash_regexes_len);
            pattern++;
            pattern_len--;
        } else if (pattern[0] == '!') {
            patterns_p = &(ig->invert_regexes);
            patterns_len = &(ig->invert_regexes_len);
            pattern++;
            pattern_len--;
        } else {
            patterns_p = &(ig->regexes);
            patterns_len = &(ig->regexes_len);
        }
    } else {
        if (pattern[0] == '/') {
            patterns_p = &(ig->slash_names);
            patterns_len = &(ig->slash_names_len);
            pattern++;
            pattern_len--;
        } else {
            patterns_p = &(ig->names);
            patterns_len = &(ig->names_len);
        }
    }

    ++*patterns_len;

    char **patterns;

    /* a balanced binary tree is best for performance, but I'm lazy */
    *patterns_p = patterns = ag_realloc(*patterns_p, (*patterns_len) * sizeof(char *));
    /* TODO: de-dupe these patterns */
    for (i = *patterns_len - 1; i > 0; i--) {
        if (strcmp(pattern, patterns[i - 1]) > 0) {
            break;
        }
        patterns[i] = patterns[i - 1];
    }
    patterns[i] = ag_strndup(pattern, pattern_len);
    log_debug("added ignore pattern %s to %s", pattern,
              ig == root_ignores ? "root ignores" : ig->abs_path);
}