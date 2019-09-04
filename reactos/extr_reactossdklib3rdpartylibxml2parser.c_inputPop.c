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
typedef  int /*<<< orphan*/ * xmlParserInputPtr ;
typedef  TYPE_1__* xmlParserCtxtPtr ;
struct TYPE_3__ {int inputNr; int /*<<< orphan*/ ** inputTab; int /*<<< orphan*/ * input; } ;

/* Variables and functions */

xmlParserInputPtr
inputPop(xmlParserCtxtPtr ctxt)
{
    xmlParserInputPtr ret;

    if (ctxt == NULL)
        return(NULL);
    if (ctxt->inputNr <= 0)
        return (NULL);
    ctxt->inputNr--;
    if (ctxt->inputNr > 0)
        ctxt->input = ctxt->inputTab[ctxt->inputNr - 1];
    else
        ctxt->input = NULL;
    ret = ctxt->inputTab[ctxt->inputNr];
    ctxt->inputTab[ctxt->inputNr] = NULL;
    return (ret);
}