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
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  TYPE_1__* xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlDoc ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_5__ {int standalone; int compression; int /*<<< orphan*/  charset; int /*<<< orphan*/  properties; scalar_t__ parseFlags; struct TYPE_5__* doc; int /*<<< orphan*/ * version; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_CHAR_ENCODING_UTF8 ; 
 int /*<<< orphan*/  XML_DOCUMENT_NODE ; 
 int /*<<< orphan*/  XML_DOC_USERBUILT ; 
 scalar_t__ __xmlRegisterCallbacks ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xmlRegisterNodeDefaultValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlStrdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlTreeErrMemory (char*) ; 

xmlDocPtr
xmlNewDoc(const xmlChar *version) {
    xmlDocPtr cur;

    if (version == NULL)
	version = (const xmlChar *) "1.0";

    /*
     * Allocate a new document and fill the fields.
     */
    cur = (xmlDocPtr) xmlMalloc(sizeof(xmlDoc));
    if (cur == NULL) {
	xmlTreeErrMemory("building doc");
	return(NULL);
    }
    memset(cur, 0, sizeof(xmlDoc));
    cur->type = XML_DOCUMENT_NODE;

    cur->version = xmlStrdup(version);
    if (cur->version == NULL) {
	xmlTreeErrMemory("building doc");
	xmlFree(cur);
	return(NULL);
    }
    cur->standalone = -1;
    cur->compression = -1; /* not initialized */
    cur->doc = cur;
    cur->parseFlags = 0;
    cur->properties = XML_DOC_USERBUILT;
    /*
     * The in memory encoding is always UTF8
     * This field will never change and would
     * be obsolete if not for binary compatibility.
     */
    cur->charset = XML_CHAR_ENCODING_UTF8;

    if ((__xmlRegisterCallbacks) && (xmlRegisterNodeDefaultValue))
	xmlRegisterNodeDefaultValue((xmlNodePtr)cur);
    return(cur);
}