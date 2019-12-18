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
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  scalar_t__ xmlChar ;
struct TYPE_3__ {scalar_t__ const* str_xml; scalar_t__ const* str_xml_ns; int nsNr; scalar_t__ const** nsTab; } ;

/* Variables and functions */

__attribute__((used)) static const xmlChar *
xmlGetNamespace(xmlParserCtxtPtr ctxt, const xmlChar *prefix) {
    int i;

    if (prefix == ctxt->str_xml) return(ctxt->str_xml_ns);
    for (i = ctxt->nsNr - 2;i >= 0;i-=2)
        if (ctxt->nsTab[i] == prefix) {
	    if ((prefix == NULL) && (*ctxt->nsTab[i + 1] == 0))
	        return(NULL);
	    return(ctxt->nsTab[i + 1]);
	}
    return(NULL);
}