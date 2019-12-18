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
typedef  int /*<<< orphan*/  xmlChar ;
typedef  scalar_t__ ptrdiff_t ;
struct TYPE_4__ {int /*<<< orphan*/ * attsSpecial; int /*<<< orphan*/  dict; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlErrMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlHashAddEntry2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void*) ; 
 int /*<<< orphan*/ * xmlHashCreateDict (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlHashLookup2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
xmlAddSpecialAttr(xmlParserCtxtPtr ctxt,
		  const xmlChar *fullname,
		  const xmlChar *fullattr,
		  int type)
{
    if (ctxt->attsSpecial == NULL) {
        ctxt->attsSpecial = xmlHashCreateDict(10, ctxt->dict);
	if (ctxt->attsSpecial == NULL)
	    goto mem_error;
    }

    if (xmlHashLookup2(ctxt->attsSpecial, fullname, fullattr) != NULL)
        return;

    xmlHashAddEntry2(ctxt->attsSpecial, fullname, fullattr,
                     (void *) (ptrdiff_t) type);
    return;

mem_error:
    xmlErrMemory(ctxt, NULL);
    return;
}