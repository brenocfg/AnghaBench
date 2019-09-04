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
typedef  int /*<<< orphan*/  (* CECallback ) (struct cache_entry*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  cache_entry_free (struct cache_entry*) ; 
 struct cache_entry** calloc (int,int) ; 
 struct cache_entry* create_renamed_cache_entry (struct cache_entry*,char const*,char const*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strconcat (char const*,char*,int /*<<< orphan*/ *) ; 
 int index_name_pos (struct index_state*,char const*,int) ; 
 int /*<<< orphan*/  memmove (struct cache_entry**,struct cache_entry**,int) ; 
 int /*<<< orphan*/  remove_index_entry_at (struct index_state*,int) ; 
 int /*<<< orphan*/  remove_name_hash (struct index_state*,struct cache_entry*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct cache_entry **
create_renamed_cache_entries (struct index_state *istate,
                              const char *src_path, const char *dst_path,
                              int *n_entries,
                              CECallback cb_after_rename,
                              void *user_data)
{
    struct cache_entry *ce, **ret = NULL;

    int src_pathlen = strlen(src_path);
    int pos = index_name_pos (istate, src_path, src_pathlen);

    /* Exact match, rename that entry. */
    if (pos >= 0) {
        ce = istate->cache[pos];
        ret = calloc (1, sizeof(struct cache_entry *));
        *ret = create_renamed_cache_entry (ce, src_path, dst_path);
        *n_entries = 1;

        remove_index_entry_at (istate, pos);

        return ret;
    }

    /* Otherwise it may be a prefix match, rename all entries begin with this prefix.
     */

    /* -pos = (the position this entry *should* be) + 1.
     * So -pos-1 is the first entry larger than this entry.
     */
    pos = -pos-1;

    /* Add '/' to the end of prefix so that we won't match a partial path component.
     * e.g. we don't want to match 'abc' with 'abcd/ef'
     */
    char *full_src_path = g_strconcat (src_path, "/", NULL);
    ++src_pathlen;

    while (pos < istate->cache_nr) {
        ce = istate->cache[pos];
        if (strncmp (ce->name, full_src_path, src_pathlen) < 0) {
            ++pos;
        } else
            break;
    }

    if (pos == istate->cache_nr) {
        g_free (full_src_path);
        *n_entries = 0;
        return NULL;
    }

    int i = pos;
    while (i < istate->cache_nr) {
        ce = istate->cache[i];
        if (strncmp (ce->name, full_src_path, src_pathlen) == 0) {
            ++i;
        } else
            break;
    }
    g_free (full_src_path);

    if (i == pos) {
        *n_entries = 0;
        return NULL;
    }

    *n_entries = (i - pos);
    ret = calloc (*n_entries, sizeof(struct cache_entry *));

    for (i = pos; i < pos + *n_entries; ++i) {
        ce = istate->cache[i];

        ret[i - pos] = create_renamed_cache_entry (ce, src_path, dst_path);

        if (cb_after_rename)
            cb_after_rename (ret[i-pos], user_data);

        remove_name_hash(istate, ce);
        cache_entry_free (ce);
    }

    if (i < istate->cache_nr)
        memmove (istate->cache + pos,
                 istate->cache + i,
                 (istate->cache_nr - i) * sizeof(struct cache_entry *));
    istate->cache_nr -= (i - pos);
    istate->cache_changed = 1;

    return ret;
}