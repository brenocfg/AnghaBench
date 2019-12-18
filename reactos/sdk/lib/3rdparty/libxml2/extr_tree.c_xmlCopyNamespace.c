#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
struct TYPE_5__ {int type; int /*<<< orphan*/  prefix; int /*<<< orphan*/  href; } ;

/* Variables and functions */
#define  XML_LOCAL_NAMESPACE 128 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 TYPE_1__* xmlNewNs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

xmlNsPtr
xmlCopyNamespace(xmlNsPtr cur) {
    xmlNsPtr ret;

    if (cur == NULL) return(NULL);
    switch (cur->type) {
	case XML_LOCAL_NAMESPACE:
	    ret = xmlNewNs(NULL, cur->href, cur->prefix);
	    break;
	default:
#ifdef DEBUG_TREE
	    xmlGenericError(xmlGenericErrorContext,
		    "xmlCopyNamespace: invalid type %d\n", cur->type);
#endif
	    return(NULL);
    }
    return(ret);
}