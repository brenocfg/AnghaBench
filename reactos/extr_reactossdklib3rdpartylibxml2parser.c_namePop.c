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
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_3__ {int nameNr; int /*<<< orphan*/ ** nameTab; int /*<<< orphan*/ * name; } ;

/* Variables and functions */

const xmlChar *
namePop(xmlParserCtxtPtr ctxt)
{
    const xmlChar *ret;

    if ((ctxt == NULL) || (ctxt->nameNr <= 0))
        return (NULL);
    ctxt->nameNr--;
    if (ctxt->nameNr > 0)
        ctxt->name = ctxt->nameTab[ctxt->nameNr - 1];
    else
        ctxt->name = NULL;
    ret = ctxt->nameTab[ctxt->nameNr];
    ctxt->nameTab[ctxt->nameNr] = NULL;
    return (ret);
}