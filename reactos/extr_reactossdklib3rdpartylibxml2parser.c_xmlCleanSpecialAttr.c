#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserCtxtPtr ;
struct TYPE_4__ {int /*<<< orphan*/ * attsSpecial; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlCleanSpecialAttrCallback ; 
 int /*<<< orphan*/  xmlHashFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlHashScanFull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ xmlHashSize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xmlCleanSpecialAttr(xmlParserCtxtPtr ctxt)
{
    if (ctxt->attsSpecial == NULL)
        return;

    xmlHashScanFull(ctxt->attsSpecial, xmlCleanSpecialAttrCallback, ctxt);

    if (xmlHashSize(ctxt->attsSpecial) == 0) {
        xmlHashFree(ctxt->attsSpecial, NULL);
        ctxt->attsSpecial = NULL;
    }
    return;
}