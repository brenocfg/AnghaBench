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
struct index_state {int dummy; } ;
typedef  int /*<<< orphan*/  SeafStat ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/  add_empty_dir_to_index (struct index_state*,char*,int /*<<< orphan*/ *) ; 
 char* g_build_filename (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_path_get_dirname (char const*) ; 
 int /*<<< orphan*/ * index_name_exists (struct index_state*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_empty_dir (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ seaf_stat (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
try_add_empty_parent_dir_entry_from_wt (const char *worktree,
                                        struct index_state *istate,
                                        GList *ignore_list,
                                        const char *path)
{
    if (index_name_exists (istate, path, strlen(path), 0) != NULL)
        return;

    char *parent_dir = g_path_get_dirname (path);

    /* Parent dir is the worktree dir. */
    if (strcmp (parent_dir, ".") == 0) {
        g_free (parent_dir);
        return;
    }

    char *full_dir = g_build_filename (worktree, parent_dir, NULL);
    SeafStat st;
    if (seaf_stat (full_dir, &st) < 0) {
        goto out;
    }

    if (is_empty_dir (full_dir, ignore_list)) {
#ifdef WIN32
        wchar_t *parent_dir_w = g_utf8_to_utf16 (parent_dir, -1, NULL, NULL, NULL);
        wchar_t *pw;
        for (pw = parent_dir_w; *pw != L'\0'; ++pw)
            if (*pw == L'/')
                *pw = L'\\';

        wchar_t *long_path = win32_83_path_to_long_path (worktree,
                                                         parent_dir_w,
                                                         wcslen(parent_dir_w));
        g_free (parent_dir_w);
        if (!long_path) {
            seaf_warning ("Convert %s to long path failed.\n", parent_dir);
            goto out;
        }

        char *utf8_path = g_utf16_to_utf8 (long_path, -1, NULL, NULL, NULL);
        if (!utf8_path) {
            g_free (long_path);
            goto out;
        }

        char *p;
        for (p = utf8_path; *p != 0; ++p)
            if (*p == '\\')
                *p = '/';
        g_free (long_path);

        add_empty_dir_to_index (istate, utf8_path, &st);
#else
        add_empty_dir_to_index (istate, parent_dir, &st);
#endif
    }

out:
    g_free (parent_dir);
    g_free (full_dir);
}