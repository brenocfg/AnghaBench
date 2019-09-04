#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  const* prefix; } ;

/* Variables and functions */
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static xmlNsPtr
xmlTreeNSListLookupByPrefix(xmlNsPtr nsList, const xmlChar *prefix)
{
    if (nsList == NULL)
	return (NULL);
    {
	xmlNsPtr ns;
	ns = nsList;
	do {
	    if ((prefix == ns->prefix) ||
		xmlStrEqual(prefix, ns->prefix)) {
		return (ns);
	    }
	    ns = ns->next;
	} while (ns != NULL);
    }
    return (NULL);
}