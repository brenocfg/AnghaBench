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
struct index_state {int cache_nr; int cache_changed; struct cache_entry** cache; } ;
struct cache_entry {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cache_entry_free (struct cache_entry*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strconcat (char const*,char*,int /*<<< orphan*/ *) ; 
 int index_name_pos (struct index_state*,char const*,int) ; 
 int /*<<< orphan*/  memmove (struct cache_entry**,struct cache_entry**,int) ; 
 int /*<<< orphan*/  remove_index_entry_at (struct index_state*,int) ; 
 int /*<<< orphan*/  remove_name_hash (struct index_state*,struct cache_entry*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

int
remove_from_index_with_prefix (struct index_state *istate, const char *path_prefix,
                               gboolean *not_found)
{
    int pathlen = strlen(path_prefix);
    int pos = index_name_pos (istate, path_prefix, pathlen);
    struct cache_entry *ce;

    if (not_found)
        *not_found = FALSE;

    /* Exact match, remove that entry. */
    if (pos >= 0) {
        remove_index_entry_at (istate, pos);
        return 0;
    }

    /* Otherwise it may be a prefix match, remove all entries begin with this prefix.
     */

    /* -pos = (the position this entry *should* be) + 1.
     * So -pos-1 is the first entry larger than this entry.
     */
    pos = -pos-1;

    /* Add '/' to the end of prefix so that we won't match a partial path component.
     * e.g. we don't want to match 'abc' with 'abcd/ef'
     */
    char *full_path_prefix = g_strconcat (path_prefix, "/", NULL);
    ++pathlen;

    while (pos < istate->cache_nr) {
        ce = istate->cache[pos];
        if (strncmp (ce->name, full_path_prefix, pathlen) < 0) {
            ++pos;
        } else
            break;
    }

    if (pos == istate->cache_nr) {
        g_free (full_path_prefix);
        if (not_found)
            *not_found = TRUE;
        return 0;
    }

    int i = pos;
    while (i < istate->cache_nr) {
        ce = istate->cache[i];
        if (strncmp (ce->name, full_path_prefix, pathlen) == 0) {
            remove_name_hash(istate, ce);
            cache_entry_free (ce);
            ++i;
        } else
            break;
    }
    g_free (full_path_prefix);

    /* No match. */
    if (i == pos) {
        if (not_found)
            *not_found = TRUE;
        return 0;
    }

    if (i < istate->cache_nr)
        memmove (istate->cache + pos,
                 istate->cache + i,
                 (istate->cache_nr - i) * sizeof(struct cache_entry *));
    istate->cache_nr -= (i - pos);
    istate->cache_changed = 1;

    return 0;
}