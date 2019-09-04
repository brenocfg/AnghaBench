#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_2__ {int /*<<< orphan*/  sync_extra_temp_file; } ;
typedef  int /*<<< orphan*/  GPatternSpec ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SEAF_DIR_NAME_LEN ; 
 int /*<<< orphan*/  TRUE ; 
 char* g_build_path (char*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_pattern_match_string (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  g_utf8_validate (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** ignore_patterns ; 
 int /*<<< orphan*/ ** office_temp_ignore_patterns ; 
 TYPE_1__* seaf ; 
 scalar_t__ seaf_repo_check_ignore_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 
 scalar_t__ strchr (char const*,char) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static gboolean
should_ignore(const char *basepath, const char *filename, void *data)
{
    GPatternSpec **spec = ignore_patterns;
    GList *ignore_list = (GList *)data;

    if (!g_utf8_validate (filename, -1, NULL)) {
        seaf_warning ("File name %s contains non-UTF8 characters, skip.\n", filename);
        return TRUE;
    }

    /* Ignore file/dir if its name is too long. */
    if (strlen(filename) >= SEAF_DIR_NAME_LEN)
        return TRUE;

    if (strchr (filename, '/'))
        return TRUE;

    while (*spec) {
        if (g_pattern_match_string(*spec, filename))
            return TRUE;
        spec++;
    }

    if (!seaf->sync_extra_temp_file) {
        spec = office_temp_ignore_patterns;
        while (*spec) {
            if (g_pattern_match_string(*spec, filename))
                return TRUE;
            spec++;
        }
    }

    if (basepath) {
        char *fullpath = g_build_path ("/", basepath, filename, NULL);
        if (seaf_repo_check_ignore_file (ignore_list, fullpath)) {
            g_free (fullpath);
            return TRUE;
        }
        g_free (fullpath);
    }

    return FALSE;
}