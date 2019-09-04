#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* data; struct TYPE_17__* next; } ;
struct TYPE_16__ {int /*<<< orphan*/  commit_id; } ;
typedef  TYPE_1__ SeafCommit ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 TYPE_1__** calloc (int,int) ; 
 int /*<<< orphan*/  compare_commit_by_time ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_list_free (TYPE_2__*) ; 
 TYPE_2__* g_list_insert_sorted_with_data (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int g_list_length (TYPE_2__*) ; 
 TYPE_2__* merge_bases_many (TYPE_1__*,int,TYPE_1__**) ; 
 int /*<<< orphan*/  seaf_commit_unref (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GList *
get_independent_commits (GList *commits)
{
    SeafCommit **rslt;
    GList *list, *result;
    int cnt, i, j;
    SeafCommit *c;

    g_debug ("Get independent commits.\n");

    cnt = g_list_length (commits);

    rslt = calloc(cnt, sizeof(*rslt));
    for (list = commits, i = 0; list; list = list->next)
        rslt[i++] = list->data;
    g_list_free (commits);

    for (i = 0; i < cnt - 1; i++) {
        for (j = i+1; j < cnt; j++) {
            if (!rslt[i] || !rslt[j])
                continue;
            result = merge_bases_many(rslt[i], 1, &rslt[j]);
            for (list = result; list; list = list->next) {
                c = list->data;
                /* If two commits have fast-forward relationship,
                 * drop the older one.
                 */
                if (strcmp (rslt[i]->commit_id, c->commit_id) == 0) {
                    seaf_commit_unref (rslt[i]);
                    rslt[i] = NULL;
                }
                if (strcmp (rslt[j]->commit_id, c->commit_id) == 0) {
                    seaf_commit_unref (rslt[j]);
                    rslt[j] = NULL;
                }
                seaf_commit_unref (c);
            }
        }
    }

    /* Surviving ones in rslt[] are the independent results */
    result = NULL;
    for (i = 0; i < cnt; i++) {
        if (rslt[i])
            result = g_list_insert_sorted_with_data (result, rslt[i],
                                                     compare_commit_by_time,
                                                     NULL);
    }
    free(rslt);
    return result;
}