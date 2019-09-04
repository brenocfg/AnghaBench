#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlCharEncodingHandlerPtr ;
struct TYPE_5__ {int /*<<< orphan*/  charset; int /*<<< orphan*/ * input; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_CHAR_ENCODING_UTF8 ; 
 int /*<<< orphan*/  xmlErrInternal (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int xmlSwitchInputEncodingInt (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
xmlSwitchToEncodingInt(xmlParserCtxtPtr ctxt,
                       xmlCharEncodingHandlerPtr handler, int len) {
    int ret = 0;

    if (handler != NULL) {
        if (ctxt->input != NULL) {
	    ret = xmlSwitchInputEncodingInt(ctxt, ctxt->input, handler, len);
	} else {
	    xmlErrInternal(ctxt, "xmlSwitchToEncoding : no input\n",
	                   NULL);
	    return(-1);
	}
	/*
	 * The parsing is now done in UTF8 natively
	 */
	ctxt->charset = XML_CHAR_ENCODING_UTF8;
    } else
	return(-1);
    return(ret);
}