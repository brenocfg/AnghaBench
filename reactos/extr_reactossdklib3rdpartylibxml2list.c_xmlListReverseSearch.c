#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xmlListPtr ;
typedef  TYPE_1__* xmlLinkPtr ;
struct TYPE_3__ {void* data; } ;

/* Variables and functions */
 TYPE_1__* xmlListLinkReverseSearch (int /*<<< orphan*/ *,void*) ; 

void *
xmlListReverseSearch(xmlListPtr l, void *data)
{
    xmlLinkPtr lk;
    if (l == NULL)
        return(NULL);
    lk = xmlListLinkReverseSearch(l, data);
    if (lk)
        return (lk->data);
    return NULL;
}