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
struct TYPE_4__ {int /*<<< orphan*/ * input; } ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlParseAttValueInternal (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

xmlChar *
xmlParseAttValue(xmlParserCtxtPtr ctxt) {
    if ((ctxt == NULL) || (ctxt->input == NULL)) return(NULL);
    return(xmlParseAttValueInternal(ctxt, NULL, NULL, 0));
}