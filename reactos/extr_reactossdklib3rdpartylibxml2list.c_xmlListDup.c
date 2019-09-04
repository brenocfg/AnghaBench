#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlListPtr ;
struct TYPE_7__ {int /*<<< orphan*/  linkCompare; } ;

/* Variables and functions */
 scalar_t__ xmlListCopy (TYPE_1__*,TYPE_1__* const) ; 
 TYPE_1__* xmlListCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

xmlListPtr
xmlListDup(const xmlListPtr old)
{
    xmlListPtr cur;

    if (old == NULL)
        return(NULL);
    /* Hmmm, how to best deal with allocation issues when copying
     * lists. If there is a de-allocator, should responsibility lie with
     * the new list or the old list. Surely not both. I'll arbitrarily
     * set it to be the old list for the time being whilst I work out
     * the answer
     */
    if (NULL ==(cur = xmlListCreate(NULL, old->linkCompare)))
        return (NULL);
    if (0 != xmlListCopy(cur, old))
        return NULL;
    return cur;
}