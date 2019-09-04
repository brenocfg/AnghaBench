#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlNode ;
typedef  TYPE_2__* xmlEntityPtr ;
typedef  int /*<<< orphan*/  xmlDoc ;
typedef  char xmlChar ;
struct TYPE_8__ {int /*<<< orphan*/  content; } ;
struct TYPE_7__ {struct TYPE_7__* last; struct TYPE_7__* children; int /*<<< orphan*/  content; void* name; int /*<<< orphan*/ * doc; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_ENTITY_REF_NODE ; 
 scalar_t__ __xmlRegisterCallbacks ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* xmlGetDocEntity (int /*<<< orphan*/  const*,void*) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xmlRegisterNodeDefaultValue (TYPE_1__*) ; 
 void* xmlStrdup (char const*) ; 
 int xmlStrlen (char const*) ; 
 void* xmlStrndup (char const*,int) ; 
 int /*<<< orphan*/  xmlTreeErrMemory (char*) ; 

xmlNodePtr
xmlNewReference(const xmlDoc *doc, const xmlChar *name) {
    xmlNodePtr cur;
    xmlEntityPtr ent;

    if (name == NULL)
        return(NULL);

    /*
     * Allocate a new node and fill the fields.
     */
    cur = (xmlNodePtr) xmlMalloc(sizeof(xmlNode));
    if (cur == NULL) {
	xmlTreeErrMemory("building reference");
	return(NULL);
    }
    memset(cur, 0, sizeof(xmlNode));
    cur->type = XML_ENTITY_REF_NODE;

    cur->doc = (xmlDoc *)doc;
    if (name[0] == '&') {
        int len;
        name++;
	len = xmlStrlen(name);
	if (name[len - 1] == ';')
	    cur->name = xmlStrndup(name, len - 1);
	else
	    cur->name = xmlStrndup(name, len);
    } else
	cur->name = xmlStrdup(name);

    ent = xmlGetDocEntity(doc, cur->name);
    if (ent != NULL) {
	cur->content = ent->content;
	/*
	 * The parent pointer in entity is a DTD pointer and thus is NOT
	 * updated.  Not sure if this is 100% correct.
	 *  -George
	 */
	cur->children = (xmlNodePtr) ent;
	cur->last = (xmlNodePtr) ent;
    }

    if ((__xmlRegisterCallbacks) && (xmlRegisterNodeDefaultValue))
	xmlRegisterNodeDefaultValue(cur);
    return(cur);
}