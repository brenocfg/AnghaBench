#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xmlNode ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  int /*<<< orphan*/ * xmlAttrPtr ;

/* Variables and functions */
 int /*<<< orphan*/  xmlCheckDTD ; 
 int /*<<< orphan*/ * xmlGetPropNodeInternal (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlGetPropNodeValueInternal (int /*<<< orphan*/ *) ; 

xmlChar *
xmlGetNsProp(const xmlNode *node, const xmlChar *name, const xmlChar *nameSpace) {
    xmlAttrPtr prop;

    prop = xmlGetPropNodeInternal(node, name, nameSpace, xmlCheckDTD);
    if (prop == NULL)
	return(NULL);
    return(xmlGetPropNodeValueInternal(prop));
}