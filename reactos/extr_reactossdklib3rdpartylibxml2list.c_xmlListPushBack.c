#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlListPtr ;
typedef  TYPE_3__* xmlLinkPtr ;
typedef  int /*<<< orphan*/  xmlLink ;
struct TYPE_7__ {struct TYPE_7__* prev; struct TYPE_7__* next; void* data; } ;
struct TYPE_6__ {TYPE_1__* sentinel; } ;
struct TYPE_5__ {TYPE_3__* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 scalar_t__ xmlMalloc (int) ; 

int
xmlListPushBack(xmlListPtr l, void *data)
{
    xmlLinkPtr lkPlace, lkNew;

    if (l == NULL)
        return(0);
    lkPlace = l->sentinel->prev;
    /* Add the new link */
    if (NULL ==(lkNew = (xmlLinkPtr )xmlMalloc(sizeof(xmlLink)))) {
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