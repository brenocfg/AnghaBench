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
typedef  TYPE_1__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlNode ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_5__ {int /*<<< orphan*/  content; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_TEXT_NODE ; 
 scalar_t__ __xmlRegisterCallbacks ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xmlRegisterNodeDefaultValue (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlStrdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlStringText ; 
 int /*<<< orphan*/  xmlTreeErrMemory (char*) ; 

xmlNodePtr
xmlNewText(const xmlChar *content) {
    xmlNodePtr cur;

    /*
     * Allocate a new node and fill the fields.
     */
    cur = (xmlNodePtr) xmlMalloc(sizeof(xmlNode));
    if (cur == NULL) {
	xmlTreeErrMemory("building text");
	return(NULL);
    }
    memset(cur, 0, sizeof(xmlNode));
    cur->type = XML_TEXT_NODE;

    cur->name = xmlStringText;
    if (content != NULL) {
	cur->content = xmlStrdup(content);
    }

    if ((__xmlRegisterCallbacks) && (xmlRegisterNodeDefaultValue))
	xmlRegisterNodeDefaultValue(cur);
    return(cur);
}