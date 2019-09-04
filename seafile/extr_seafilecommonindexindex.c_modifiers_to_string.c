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
struct cache_entry {int ce_flags; int /*<<< orphan*/  modifier; int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int CE_REMOVE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_append_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
modifiers_to_string (GString *buf, struct index_state *istate)
{
    int i;
    struct cache_entry *ce;

    for (i = 0; i < istate->cache_nr; ++i) {
        ce = istate->cache[i];
        if (S_ISDIR(ce->ce_mode) || (ce->ce_flags & CE_REMOVE))
            continue;
        if (!ce->modifier) {
            seaf_warning ("BUG: index entry %s doesn't have modifier info.\n",
                       ce->name);
            return -1;
        }
        g_string_append_printf (buf, "%s\n", ce->modifier);
    }

    return 0;
}