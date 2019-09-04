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
typedef  int /*<<< orphan*/  xmlNsPtr ;
typedef  TYPE_1__* xmlNodePtr ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 scalar_t__ XML_ATTRIBUTE_NODE ; 
 scalar_t__ XML_ELEMENT_NODE ; 

void
xmlSetNs(xmlNodePtr node, xmlNsPtr ns) {
    if (node == NULL) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlSetNs: node == NULL\n");
#endif
	return;
    }
    if ((node->type == XML_ELEMENT_NODE) ||
        (node->type == XML_ATTRIBUTE_NODE))
	node->ns = ns;
}