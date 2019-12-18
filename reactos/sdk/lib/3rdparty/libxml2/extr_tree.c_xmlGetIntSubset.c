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
typedef  TYPE_1__* xmlNodePtr ;
typedef  int /*<<< orphan*/ * xmlDtdPtr ;
struct TYPE_5__ {scalar_t__ intSubset; TYPE_1__* children; } ;
typedef  TYPE_2__ xmlDoc ;
struct TYPE_4__ {scalar_t__ type; struct TYPE_4__* next; } ;

/* Variables and functions */
 scalar_t__ XML_DTD_NODE ; 

xmlDtdPtr
xmlGetIntSubset(const xmlDoc *doc) {
    xmlNodePtr cur;

    if (doc == NULL)
	return(NULL);
    cur = doc->children;
    while (cur != NULL) {
	if (cur->type == XML_DTD_NODE)
	    return((xmlDtdPtr) cur);
	cur = cur->next;
    }
    return((xmlDtdPtr) doc->intSubset);
}