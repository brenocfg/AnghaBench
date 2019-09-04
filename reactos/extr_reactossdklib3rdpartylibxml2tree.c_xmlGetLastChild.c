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
typedef  int /*<<< orphan*/ * xmlNodePtr ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/ * last; } ;
typedef  TYPE_1__ xmlNode ;

/* Variables and functions */
 scalar_t__ XML_NAMESPACE_DECL ; 

xmlNodePtr
xmlGetLastChild(const xmlNode *parent) {
    if ((parent == NULL) || (parent->type == XML_NAMESPACE_DECL)) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlGetLastChild : parent == NULL\n");
#endif
	return(NULL);
    }
    return(parent->last);
}