#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xmlElementTablePtr ;
typedef  TYPE_2__* xmlElementPtr ;
typedef  int /*<<< orphan*/  xmlElement ;
typedef  TYPE_3__* xmlDtdPtr ;
typedef  int /*<<< orphan*/ * xmlDictPtr ;
typedef  int /*<<< orphan*/  const xmlChar ;
struct TYPE_11__ {int /*<<< orphan*/ * elements; TYPE_1__* doc; } ;
struct TYPE_10__ {int /*<<< orphan*/  etype; void* prefix; void* name; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int /*<<< orphan*/ * dict; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_ELEMENT_DECL ; 
 int /*<<< orphan*/  XML_ELEMENT_TYPE_UNDEFINED ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlHashAddEntry2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_2__*) ; 
 int /*<<< orphan*/ * xmlHashCreateDict (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* xmlHashLookup2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  const* xmlSplitQName2 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const**) ; 
 void* xmlStrdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlVErrMemory (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static xmlElementPtr
xmlGetDtdElementDesc2(xmlDtdPtr dtd, const xmlChar *name, int create) {
    xmlElementTablePtr table;
    xmlElementPtr cur;
    xmlChar *uqname = NULL, *prefix = NULL;

    if (dtd == NULL) return(NULL);
    if (dtd->elements == NULL) {
	xmlDictPtr dict = NULL;

	if (dtd->doc != NULL)
	    dict = dtd->doc->dict;

	if (!create)
	    return(NULL);
	/*
	 * Create the Element table if needed.
	 */
	table = (xmlElementTablePtr) dtd->elements;
	if (table == NULL) {
	    table = xmlHashCreateDict(0, dict);
	    dtd->elements = (void *) table;
	}
	if (table == NULL) {
	    xmlVErrMemory(NULL, "element table allocation failed");
	    return(NULL);
	}
    }
    table = (xmlElementTablePtr) dtd->elements;

    uqname = xmlSplitQName2(name, &prefix);
    if (uqname != NULL)
        name = uqname;
    cur = xmlHashLookup2(table, name, prefix);
    if ((cur == NULL) && (create)) {
	cur = (xmlElementPtr) xmlMalloc(sizeof(xmlElement));
	if (cur == NULL) {
	    xmlVErrMemory(NULL, "malloc failed");
	    return(NULL);
	}
	memset(cur, 0, sizeof(xmlElement));
	cur->type = XML_ELEMENT_DECL;

	/*
	 * fill the structure.
	 */
	cur->name = xmlStrdup(name);
	cur->prefix = xmlStrdup(prefix);
	cur->etype = XML_ELEMENT_TYPE_UNDEFINED;

	xmlHashAddEntry2(table, name, prefix, cur);
    }
    if (prefix != NULL) xmlFree(prefix);
    if (uqname != NULL) xmlFree(uqname);
    return(cur);
}