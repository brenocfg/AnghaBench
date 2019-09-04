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
typedef  int /*<<< orphan*/  xmlNsPtr ;

/* Variables and functions */
 scalar_t__ xmlMalloc (int) ; 
 scalar_t__ xmlRealloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xmlTreeErrMemory (char*) ; 

__attribute__((used)) static int
xmlDOMWrapNSNormAddNsMapItem2(xmlNsPtr **list, int *size, int *number,
			xmlNsPtr oldNs, xmlNsPtr newNs)
{
    if (*list == NULL) {
	*list = (xmlNsPtr *) xmlMalloc(6 * sizeof(xmlNsPtr));
	if (*list == NULL) {
	    xmlTreeErrMemory("alloc ns map item");
	    return(-1);
	}
	*size = 3;
	*number = 0;
    } else if ((*number) >= (*size)) {
	*size *= 2;
	*list = (xmlNsPtr *) xmlRealloc(*list,
	    (*size) * 2 * sizeof(xmlNsPtr));
	if (*list == NULL) {
	    xmlTreeErrMemory("realloc ns map item");
	    return(-1);
	}
    }
    (*list)[2 * (*number)] = oldNs;
    (*list)[2 * (*number) +1] = newNs;
    (*number)++;
    return (0);
}