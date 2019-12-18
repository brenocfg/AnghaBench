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
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {char* name; int /*<<< orphan*/  ce_mode; } ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  IndexDirent ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compare_index_dents ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_list_sort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* g_strconcat (char const*,char*,int /*<<< orphan*/ *) ; 
 char* g_strdup (char const*) ; 
 char* g_strndup (char*,int) ; 
 int /*<<< orphan*/ * index_dirent_new (char*,int /*<<< orphan*/ ,struct cache_entry*) ; 
 int index_name_pos (struct index_state*,char const*,int) ; 
 scalar_t__ is_duplicate_dirent (int /*<<< orphan*/ *,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

GList *
list_dirents_from_index (struct index_state *istate, const char *dir)
{
    char *full_dir;
    int pathlen;
    int pos;
    struct cache_entry *ce;
    GList *dirents = NULL;
    char *path, *slash, *dname;
    gboolean is_dir;
    IndexDirent *dirent;

    if (dir[0] == 0) {
        pos = 0;
        full_dir = g_strdup(dir);
        pathlen = 0;
        goto collect_dents;
    } else {
        pathlen = strlen(dir);
        pos = index_name_pos (istate, dir, pathlen);
    }

    /* Exact match, it's an empty dir. */
    if (pos >= 0) {
        return NULL;
    }

    /* Otherwise it may be a prefix match, there may be dirents under the dir.
     */

    /* -pos = (the position this entry *should* be) + 1.
     * So -pos-1 is the first entry larger than this entry.
     */
    pos = -pos-1;

    /* Add '/' to the end of prefix so that we won't match a partial path component.
     * e.g. we don't want to match 'abc' with 'abcd/ef'
     */
    full_dir = g_strconcat (dir, "/", NULL);
    ++pathlen;

    while (pos < istate->cache_nr) {
        ce = istate->cache[pos];
        if (strncmp (ce->name, full_dir, pathlen) < 0) {
            ++pos;
        } else
            break;
    }

    /* The dir actually doesn't exist. */
    if (pos == istate->cache_nr) {
        g_free (full_dir);
        return NULL;
    }

collect_dents:
    for (; pos < istate->cache_nr; ++pos) {
        ce = istate->cache[pos];

        if (strncmp (full_dir, ce->name, pathlen) != 0)
            break;

        path = ce->name + pathlen;
        slash = strchr(path, '/');
        if (slash) {
            dname = g_strndup(path, slash - path);
            if (is_duplicate_dirent (dirents, dname)) {
                g_free (dname);
                continue;
            }

            dirent = index_dirent_new (dname, TRUE, NULL);
            dirents = g_list_prepend (dirents, dirent);
        } else {
            dname = g_strdup(path);
            is_dir = S_ISDIR(ce->ce_mode);
            dirent = index_dirent_new (dname, is_dir, ce);
            dirents = g_list_prepend (dirents, dirent);
        }
    }

    dirents = g_list_sort (dirents, compare_index_dents);

    g_free (full_dir);
    return dirents;
}