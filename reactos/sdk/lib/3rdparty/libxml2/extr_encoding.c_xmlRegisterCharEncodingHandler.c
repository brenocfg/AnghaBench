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
typedef  int /*<<< orphan*/ * xmlCharEncodingHandlerPtr ;

/* Variables and functions */
 scalar_t__ MAX_ENCODING_HANDLERS ; 
 int /*<<< orphan*/  XML_I18N_EXCESS_HANDLER ; 
 int /*<<< orphan*/  XML_I18N_NO_HANDLER ; 
 int /*<<< orphan*/ ** handlers ; 
 scalar_t__ nbCharEncodingHandler ; 
 int /*<<< orphan*/  xmlEncodingErr (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  xmlInitCharEncodingHandlers () ; 

void
xmlRegisterCharEncodingHandler(xmlCharEncodingHandlerPtr handler) {
    if (handlers == NULL) xmlInitCharEncodingHandlers();
    if ((handler == NULL) || (handlers == NULL)) {
        xmlEncodingErr(XML_I18N_NO_HANDLER,
		"xmlRegisterCharEncodingHandler: NULL handler !\n", NULL);
	return;
    }

    if (nbCharEncodingHandler >= MAX_ENCODING_HANDLERS) {
        xmlEncodingErr(XML_I18N_EXCESS_HANDLER,
	"xmlRegisterCharEncodingHandler: Too many handler registered, see %s\n",
	               "MAX_ENCODING_HANDLERS");
	return;
    }
    handlers[nbCharEncodingHandler++] = handler;
}