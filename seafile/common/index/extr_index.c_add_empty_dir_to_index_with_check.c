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
struct index_state {int cache_nr; int cache_alloc; int cache_changed; struct cache_entry** cache; } ;
struct cache_entry {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  ce ;
typedef  int /*<<< orphan*/  SeafStat ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int alloc_nr (int) ; 
 struct cache_entry* create_empty_dir_index_entry (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strconcat (char const*,char*,int /*<<< orphan*/ *) ; 
 int index_name_pos (struct index_state*,char const*,int) ; 
 int /*<<< orphan*/  memmove (struct cache_entry**,struct cache_entry**,int) ; 
 struct cache_entry** realloc (struct cache_entry**,int) ; 
 int /*<<< orphan*/  set_index_entry (struct index_state*,int,struct cache_entry*) ; 
 int strlen (char const*) ; 
 int strncmp (int /*<<< orphan*/ ,char*,int) ; 

int
add_empty_dir_to_index_with_check (struct index_state *istate,
                                   const char *path, SeafStat *st)
{
    int pathlen = strlen(path);
    int pos = index_name_pos (istate, path, pathlen);
    struct cache_entry *ce;

    /* Exact match, empty dir entry already exists. */
    if (pos >= 0) {
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
    char *full_path = g_strconcat (path, "/", NULL);
    ++pathlen;

    gboolean is_empty = TRUE;

    while (pos < istate->cache_nr) {
        ce = istate->cache[pos];
        int rc = strncmp (ce->name, full_path, pathlen);
        if (rc < 0) {
            ++pos;
        } else if (rc == 0) {
            is_empty = FALSE;
            break;
        } else
            break;
    }

    g_free (full_path);

    if (is_empty) {
        ce = create_empty_dir_index_entry (path, st);

        /* Make sure the array is big enough .. */
        if (istate->cache_nr == istate->cache_alloc) {
            istate->cache_alloc = alloc_nr(istate->cache_alloc);
            istate->cache = realloc(istate->cache,
                                    istate->cache_alloc * sizeof(struct cache_entry *));
        }

        /* Add it in.. */
        istate->cache_nr++;
        if (istate->cache_nr > pos + 1)
            memmove(istate->cache + pos + 1,
                    istate->cache + pos,
                    (istate->cache_nr - pos - 1) * sizeof(ce));
        set_index_entry(istate, pos, ce);
        istate->cache_changed = 1;
    }

    return 0;
}