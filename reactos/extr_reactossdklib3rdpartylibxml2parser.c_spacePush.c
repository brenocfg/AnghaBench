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
struct TYPE_4__ {int spaceNr; int spaceMax; int* spaceTab; int* space; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlErrMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ xmlRealloc (int*,int) ; 

__attribute__((used)) static int spacePush(xmlParserCtxtPtr ctxt, int val) {
    if (ctxt->spaceNr >= ctxt->spaceMax) {
        int *tmp;

	ctxt->spaceMax *= 2;
        tmp = (int *) xmlRealloc(ctxt->spaceTab,
	                         ctxt->spaceMax * sizeof(ctxt->spaceTab[0]));
        if (tmp == NULL) {
	    xmlErrMemory(ctxt, NULL);
	    ctxt->spaceMax /=2;
	    return(-1);
	}
	ctxt->spaceTab = tmp;
    }
    ctxt->spaceTab[ctxt->spaceNr] = val;
    ctxt->space = &ctxt->spaceTab[ctxt->spaceNr];
    return(ctxt->spaceNr++);
}