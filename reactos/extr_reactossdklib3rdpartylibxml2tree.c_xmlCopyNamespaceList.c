#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
struct TYPE_6__ {struct TYPE_6__* next; } ;

/* Variables and functions */
 TYPE_1__* xmlCopyNamespace (TYPE_1__*) ; 

xmlNsPtr
xmlCopyNamespaceList(xmlNsPtr cur) {
    xmlNsPtr ret = NULL;
    xmlNsPtr p = NULL,q;

    while (cur != NULL) {
        q = xmlCopyNamespace(cur);
	if (p == NULL) {
	    ret = p = q;
	} else {
	    p->next = q;
	    p = q;
	}
	cur = cur->next;
    }
    return(ret);
}