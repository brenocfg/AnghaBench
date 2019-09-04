#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlListPtr ;
typedef  TYPE_2__* xmlLinkPtr ;
typedef  int /*<<< orphan*/  xmlLink ;
struct TYPE_5__ {struct TYPE_5__* prev; struct TYPE_5__* next; void* data; } ;
struct TYPE_4__ {TYPE_2__* sentinel; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 scalar_t__ xmlMalloc (int) ; 

int
xmlListPushFront(xmlListPtr l, void *data)
{
    xmlLinkPtr lkPlace, lkNew;

    if (l == NULL)
        return(0);
    lkPlace = l->sentinel;
    /* Add the new link */
    lkNew = (xmlLinkPtr) xmlMalloc(sizeof(xmlLink));
    if (lkNew == NULL) {
        xmlGenericError(xmlGenericErrorContext,
		        "Cannot initialize memory for new link");
        return (0);
    }
    lkNew->data = data;
    lkNew->next = lkPlace->next;
    (lkPlace->next)->prev = lkNew;
    lkPlace->next = lkNew;
    lkNew->prev = lkPlace;
    return 1;
}