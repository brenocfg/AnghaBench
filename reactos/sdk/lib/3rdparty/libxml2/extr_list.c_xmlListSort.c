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
typedef  int /*<<< orphan*/ * xmlListPtr ;

/* Variables and functions */
 int /*<<< orphan*/  xmlListClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlListDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlListDup (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlListMerge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
xmlListSort(xmlListPtr l)
{
    xmlListPtr lTemp;

    if (l == NULL)
        return;
    if(xmlListEmpty(l))
        return;

    /* I think that the real answer is to implement quicksort, the
     * alternative is to implement some list copying procedure which
     * would be based on a list copy followed by a clear followed by
     * an insert. This is slow...
     */

    if (NULL ==(lTemp = xmlListDup(l)))
        return;
    xmlListClear(l);
    xmlListMerge(l, lTemp);
    xmlListDelete(lTemp);
    return;
}