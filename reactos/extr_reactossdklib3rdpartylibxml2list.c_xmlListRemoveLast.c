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
typedef  int /*<<< orphan*/ * xmlLinkPtr ;

/* Variables and functions */
 int /*<<< orphan*/  xmlLinkDeallocator (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlListLinkReverseSearch (int /*<<< orphan*/ *,void*) ; 

int
xmlListRemoveLast(xmlListPtr l, void *data)
{
    xmlLinkPtr lk;

    if (l == NULL)
        return(0);
    /*Find the last instance of this data */
    lk = xmlListLinkReverseSearch(l, data);
    if (lk != NULL) {
	xmlLinkDeallocator(l, lk);
        return 1;
    }
    return 0;
}