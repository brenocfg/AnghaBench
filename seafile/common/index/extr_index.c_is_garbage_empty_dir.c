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
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strconcat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int index_name_pos (struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int is_garbage_empty_dir (struct index_state *istate, struct cache_entry *ce)
{
    int ret = 0;
    int pos = index_name_pos (istate, ce->name, ce->ce_flags);

    /* Empty folder already exists in the index. */
    if (pos >= 0)
        return 0;

    /* -pos = (the position this entry *should* be) + 1.
     * So -pos-1 is the first entry larger than this entry.
     */
    pos = -pos-1;

    struct cache_entry *next;
    char *dir_name = g_strconcat (ce->name, "/", NULL);
    int this_len = strlen (ce->name) + 1;
    while (pos < istate->cache_nr) {
        next = istate->cache[pos];
        int rc = strncmp (next->name, dir_name, this_len);
        if (rc == 0) {
            ret = 1;
            break;
        } else if (rc < 0) {
            ++pos;
        } else
            break;
    }

    g_free (dir_name);
    return ret;
}