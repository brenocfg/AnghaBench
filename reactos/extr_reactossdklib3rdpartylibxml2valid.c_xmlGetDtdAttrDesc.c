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
typedef  TYPE_1__* xmlDtdPtr ;
typedef  int /*<<< orphan*/  const xmlChar ;
typedef  int /*<<< orphan*/ * xmlAttributeTablePtr ;
typedef  int /*<<< orphan*/ * xmlAttributePtr ;
struct TYPE_3__ {int /*<<< orphan*/ * attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * xmlHashLookup3 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* xmlSplitQName2 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const**) ; 

xmlAttributePtr
xmlGetDtdAttrDesc(xmlDtdPtr dtd, const xmlChar *elem, const xmlChar *name) {
    xmlAttributeTablePtr table;
    xmlAttributePtr cur;
    xmlChar *uqname = NULL, *prefix = NULL;

    if (dtd == NULL) return(NULL);
    if (dtd->attributes == NULL) return(NULL);

    table = (xmlAttributeTablePtr) dtd->attributes;
    if (table == NULL)
	return(NULL);

    uqname = xmlSplitQName2(name, &prefix);

    if (uqname != NULL) {
	cur = xmlHashLookup3(table, uqname, prefix, elem);
	if (prefix != NULL) xmlFree(prefix);
	if (uqname != NULL) xmlFree(uqname);
    } else
	cur = xmlHashLookup3(table, name, NULL, elem);
    return(cur);
}