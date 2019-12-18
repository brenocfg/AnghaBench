#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
typedef  TYPE_2__* xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  TYPE_3__* xmlAttrPtr ;
typedef  int /*<<< orphan*/  xmlAttr ;
struct TYPE_12__ {TYPE_1__* last; TYPE_1__* children; TYPE_2__* doc; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {int /*<<< orphan*/ * dict; } ;
struct TYPE_10__ {struct TYPE_10__* next; struct TYPE_10__* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_ATTRIBUTE_NODE ; 
 scalar_t__ __xmlRegisterCallbacks ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmlDictLookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xmlRegisterNodeDefaultValue (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlStrdup (int /*<<< orphan*/  const*) ; 
 TYPE_1__* xmlStringGetNodeList (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlTreeErrMemory (char*) ; 

xmlAttrPtr
xmlNewDocProp(xmlDocPtr doc, const xmlChar *name, const xmlChar *value) {
    xmlAttrPtr cur;

    if (name == NULL) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlNewDocProp : name == NULL\n");
#endif
	return(NULL);
    }

    /*
     * Allocate a new property and fill the fields.
     */
    cur = (xmlAttrPtr) xmlMalloc(sizeof(xmlAttr));
    if (cur == NULL) {
	xmlTreeErrMemory("building attribute");
	return(NULL);
    }
    memset(cur, 0, sizeof(xmlAttr));
    cur->type = XML_ATTRIBUTE_NODE;

    if ((doc != NULL) && (doc->dict != NULL))
	cur->name = xmlDictLookup(doc->dict, name, -1);
    else
	cur->name = xmlStrdup(name);
    cur->doc = doc;
    if (value != NULL) {
	xmlNodePtr tmp;

	cur->children = xmlStringGetNodeList(doc, value);
	cur->last = NULL;

	tmp = cur->children;
	while (tmp != NULL) {
	    tmp->parent = (xmlNodePtr) cur;
	    if (tmp->next == NULL)
		cur->last = tmp;
	    tmp = tmp->next;
	}
    }

    if ((__xmlRegisterCallbacks) && (xmlRegisterNodeDefaultValue))
	xmlRegisterNodeDefaultValue((xmlNodePtr)cur);
    return(cur);
}