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
struct TYPE_3__ {int spaceNr; int* space; int* spaceTab; } ;

/* Variables and functions */

__attribute__((used)) static int spacePop(xmlParserCtxtPtr ctxt) {
    int ret;
    if (ctxt->spaceNr <= 0) return(0);
    ctxt->spaceNr--;
    if (ctxt->spaceNr > 0)
	ctxt->space = &ctxt->spaceTab[ctxt->spaceNr - 1];
    else
        ctxt->space = &ctxt->spaceTab[0];
    ret = ctxt->spaceTab[ctxt->spaceNr];
    ctxt->spaceTab[ctxt->spaceNr] = -1;
    return(ret);
}