#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * data; struct TYPE_5__* next; } ;
typedef  int /*<<< orphan*/  SeafCommit ;
typedef  TYPE_1__ GList ;

/* Variables and functions */
 int /*<<< orphan*/ ** calloc (int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_list_free (TYPE_1__*) ; 
 int g_list_length (TYPE_1__*) ; 
 TYPE_1__* merge_bases_many (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

SeafCommit *
get_merge_base (SeafCommit *head, SeafCommit *remote)
{
    GList *result, *iter;
    SeafCommit *one, **twos;
    int n, i;
    SeafCommit *ret = NULL;

    one = head;
    twos = (SeafCommit **) calloc (1, sizeof(SeafCommit *));
    twos[0] = remote;
    n = 1;
    result = merge_bases_many (one, n, twos);
    free (twos);
    if (!result || !result->next)
        goto done;

    /*
     * More than one common ancestors.
     * Loop until the oldest common ancestor is found.
     */
    while (1) {
        n = g_list_length (result) - 1;
        one = result->data;
        twos = calloc (n, sizeof(SeafCommit *));
        for (iter = result->next, i = 0; i < n; iter = iter->next, i++) {
            twos[i] = iter->data;
        }
        g_list_free (result);

        result = merge_bases_many (one, n, twos);
        free (twos);
        if (!result || !result->next)
            break;
    }

done:
    if (result)
        ret = result->data;
    g_list_free (result);

    return ret;
}