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
struct index_state {int cache_nr; int /*<<< orphan*/ * cache; } ;
struct cache_entry {int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ADD_CACHE_NEW_ONLY ; 
 int ADD_CACHE_OK_TO_ADD ; 
 scalar_t__ ce_same_name (int /*<<< orphan*/ ,struct cache_entry*) ; 
 scalar_t__ ce_stage (struct cache_entry*) ; 
 int index_name_pos (struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_empty_parent_dir_entry (struct index_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_index_entry_at (struct index_state*,int) ; 
 int /*<<< orphan*/  replace_index_entry (struct index_state*,int,struct cache_entry*) ; 

__attribute__((used)) static int add_index_entry_with_check(struct index_state *istate, struct cache_entry *ce, int option)
{
    int pos;
    int ok_to_add = option & ADD_CACHE_OK_TO_ADD;
    /* int ok_to_replace = option & ADD_CACHE_OK_TO_REPLACE; */
    /* int skip_df_check = option & ADD_CACHE_SKIP_DFCHECK; */
    int new_only = option & ADD_CACHE_NEW_ONLY;

    remove_empty_parent_dir_entry (istate, ce->name);

    pos = index_name_pos(istate, ce->name, ce->ce_flags);

    /* existing match? Just replace it. */
    if (pos >= 0) {
        if (!new_only)
            replace_index_entry(istate, pos, ce);
        return 0;
    }
    pos = -pos-1;

    /*
     * Inserting a merged entry ("stage 0") into the index
     * will always replace all non-merged entries..
     */
    if (pos < istate->cache_nr && ce_stage(ce) == 0) {
        while (ce_same_name(istate->cache[pos], ce)) {
            ok_to_add = 1;
            if (!remove_index_entry_at(istate, pos))
                break;
        }
    }

    if (!ok_to_add)
        return -1;
    /* if (!verify_path(ce->name)) { */
    /*     seaf_warning("Invalid path '%s'\n", ce->name); */
    /*     return -1; */
    /* } */

    /* if (!skip_df_check && */
    /*     check_file_directory_conflict(istate, ce, pos, ok_to_replace)) { */
    /*     if (!ok_to_replace) */
    /*         return error("'%s' appears as both a file and as a directory", */
    /*                  ce->name); */
    /*     pos = index_name_pos(istate, ce->name, ce->ce_flags); */
    /*     pos = -pos-1; */
    /* } */
    return pos + 1;
}