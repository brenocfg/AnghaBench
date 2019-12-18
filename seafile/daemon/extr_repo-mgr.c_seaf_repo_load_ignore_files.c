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
struct TYPE_3__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ SeafStat ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  IGNORE_FILE ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  PATH_SEPERATOR ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 char* g_build_path (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_fopen (char*,char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,char*) ; 
 char* g_strdup_printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  g_strstrip (char*) ; 
 scalar_t__ seaf_stat (char*,TYPE_1__*) ; 
 int strlen (char*) ; 

GList *seaf_repo_load_ignore_files (const char *worktree)
{
    GList *list = NULL;
    SeafStat st;
    FILE *fp;
    char *full_path, *pattern;
    char path[PATH_MAX];

    full_path = g_build_path (PATH_SEPERATOR, worktree,
                              IGNORE_FILE, NULL);
    if (seaf_stat (full_path, &st) < 0)
        goto error;
    if (!S_ISREG(st.st_mode))
        goto error;
    fp = g_fopen(full_path, "r");
    if (fp == NULL)
        goto error;

    while (fgets(path, PATH_MAX, fp) != NULL) {
        /* remove leading and trailing whitespace, including \n \r. */
        g_strstrip (path);

        /* ignore comment and blank line */
        if (path[0] == '#' || path[0] == '\0')
            continue;

        /* Change 'foo/' to 'foo/ *'. */
        if (path[strlen(path)-1] == '/')
            pattern = g_strdup_printf("%s/%s*", worktree, path);
        else
            pattern = g_strdup_printf("%s/%s", worktree, path);

        list = g_list_prepend(list, pattern);
    }

    fclose(fp);
    g_free (full_path);
    return list;

error:
    g_free (full_path);
    return NULL;
}