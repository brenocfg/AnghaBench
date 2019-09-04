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
typedef  int /*<<< orphan*/  xmlLink ;
struct TYPE_3__ {struct TYPE_3__* prev; struct TYPE_3__* next; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 TYPE_1__* xmlListHigherSearch (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ xmlMalloc (int) ; 

int xmlListAppend(xmlListPtr l, void *data)
{
    xmlLinkPtr lkPlace, lkNew;

    if (l == NULL)
        return(1);
    lkPlace = xmlListHigherSearch(l, data);
    /* Add the new link */
    lkNew = (xmlLinkPtr) xmlMalloc(sizeof(xmlLink));
    if (lkNew == NULL) {
        xmlGenericError(xmlGenericErrorContext,
		        "Cannot initialize memory for new link");
        return (1);
    }
    lkNew->data = data;
    lkNew->next = lkPlace->next;
    (lkPlace->next)->prev = lkNew;
    lkPlace->next = lkNew;
    lkNew->prev = lkPlace;
    return 0;
}