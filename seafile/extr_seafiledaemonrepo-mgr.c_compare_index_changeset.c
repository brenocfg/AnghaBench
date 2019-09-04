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
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  sec; } ;
struct cache_entry {int ce_flags; TYPE_1__ ce_mtime; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  sha1; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  ChangeSet ;

/* Variables and functions */
 int CE_ADDED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  changeset_check_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
compare_index_changeset (struct index_state *istate, ChangeSet *changeset)
{
    struct cache_entry *ce;
    int i;
    gboolean ret = TRUE;

    for (i = 0; i < istate->cache_nr; ++i) {
        ce = istate->cache[i];

        if (!(ce->ce_flags & CE_ADDED))
            continue;

        seaf_message ("checking %s in changeset.\n", ce->name);

        if (!changeset_check_path (changeset, ce->name,
                                   ce->sha1, ce->ce_mode, ce->ce_mtime.sec))
            ret = FALSE;
    }

    return ret;
}