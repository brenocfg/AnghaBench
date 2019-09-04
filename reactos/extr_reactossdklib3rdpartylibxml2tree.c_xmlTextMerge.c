#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
struct TYPE_8__ {scalar_t__ type; scalar_t__ name; int /*<<< orphan*/  content; } ;

/* Variables and functions */
 scalar_t__ XML_TEXT_NODE ; 
 int /*<<< orphan*/  xmlFreeNode (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlNodeAddContent (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlUnlinkNode (TYPE_1__*) ; 

xmlNodePtr
xmlTextMerge(xmlNodePtr first, xmlNodePtr second) {
    if (first == NULL) return(second);
    if (second == NULL) return(first);
    if (first->type != XML_TEXT_NODE) return(first);
    if (second->type != XML_TEXT_NODE) return(first);
    if (second->name != first->name)
	return(first);
    xmlNodeAddContent(first, second->content);
    xmlUnlinkNode(second);
    xmlFreeNode(second);
    return(first);
}