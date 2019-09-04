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
typedef  scalar_t__ gboolean ;
struct TYPE_2__ {int /*<<< orphan*/  commit_mgr; } ;
typedef  int /*<<< orphan*/  SeafCommit ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int /*<<< orphan*/  compare_commit_by_time ; 
 int /*<<< orphan*/ * g_hash_table_lookup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  g_hash_table_replace (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * g_list_insert_sorted_with_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* g_strdup (char const*) ; 
 TYPE_1__* seaf ; 
 int /*<<< orphan*/ * seaf_commit_manager_get_commit (int /*<<< orphan*/ ,char const*,int,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 

__attribute__((used)) inline static int
insert_parent_commit (GList **list, GHashTable *hash,
                      const char *repo_id, int version,
                      const char *parent_id, gboolean allow_truncate)
{
    SeafCommit *p;
    char *key;

    if (g_hash_table_lookup (hash, parent_id) != NULL)
        return 0;

    p = seaf_commit_manager_get_commit (seaf->commit_mgr,
                                        repo_id, version,
                                        parent_id);
    if (!p) {
        if (allow_truncate)
            return 0;
        seaf_warning ("Failed to find commit %s\n", parent_id);
        return -1;
    }

    *list = g_list_insert_sorted_with_data (*list, p,
                                           compare_commit_by_time,
                                           NULL);

    key = g_strdup (parent_id);
    g_hash_table_replace (hash, key, key);

    return 0;
}