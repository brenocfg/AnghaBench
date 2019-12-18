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
typedef  int /*<<< orphan*/  xmlChar ;
typedef  scalar_t__ xmlAttributeTablePtr ;
typedef  int /*<<< orphan*/ * xmlAttributePtr ;
struct TYPE_3__ {int /*<<< orphan*/ * attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlHashLookup3 (scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

xmlAttributePtr
xmlGetDtdQAttrDesc(xmlDtdPtr dtd, const xmlChar *elem, const xmlChar *name,
	          const xmlChar *prefix) {
    xmlAttributeTablePtr table;

    if (dtd == NULL) return(NULL);
    if (dtd->attributes == NULL) return(NULL);
    table = (xmlAttributeTablePtr) dtd->attributes;

    return(xmlHashLookup3(table, name, prefix, elem));
}