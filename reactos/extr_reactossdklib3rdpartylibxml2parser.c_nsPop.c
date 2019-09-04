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
struct TYPE_3__ {int nsNr; int /*<<< orphan*/ ** nsTab; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 

__attribute__((used)) static int
nsPop(xmlParserCtxtPtr ctxt, int nr)
{
    int i;

    if (ctxt->nsTab == NULL) return(0);
    if (ctxt->nsNr < nr) {
        xmlGenericError(xmlGenericErrorContext, "Pbm popping %d NS\n", nr);
        nr = ctxt->nsNr;
    }
    if (ctxt->nsNr <= 0)
        return (0);

    for (i = 0;i < nr;i++) {
         ctxt->nsNr--;
	 ctxt->nsTab[ctxt->nsNr] = NULL;
    }
    return(nr);
}