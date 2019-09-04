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
typedef  TYPE_1__* xmlValidCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlGenericErrorFunc ;
struct TYPE_3__ {scalar_t__ finishDtd; int /*<<< orphan*/ * userData; int /*<<< orphan*/ * error; } ;

/* Variables and functions */
 scalar_t__ XML_CTXT_FINISH_DTD_0 ; 
 scalar_t__ XML_CTXT_FINISH_DTD_1 ; 
 int /*<<< orphan*/  XML_ERR_FATAL ; 
 int /*<<< orphan*/  XML_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  XML_FROM_VALID ; 
 int /*<<< orphan*/  __xmlRaiseError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
xmlVErrMemory(xmlValidCtxtPtr ctxt, const char *extra)
{
    xmlGenericErrorFunc channel = NULL;
    xmlParserCtxtPtr pctxt = NULL;
    void *data = NULL;

    if (ctxt != NULL) {
        channel = ctxt->error;
        data = ctxt->userData;
	/* Use the special values to detect if it is part of a parsing
	   context */
	if ((ctxt->finishDtd == XML_CTXT_FINISH_DTD_0) ||
	    (ctxt->finishDtd == XML_CTXT_FINISH_DTD_1)) {
	    long delta = (char *) ctxt - (char *) ctxt->userData;
	    if ((delta > 0) && (delta < 250))
		pctxt = ctxt->userData;
	}
    }
    if (extra)
        __xmlRaiseError(NULL, channel, data,
                        pctxt, NULL, XML_FROM_VALID, XML_ERR_NO_MEMORY,
                        XML_ERR_FATAL, NULL, 0, extra, NULL, NULL, 0, 0,
                        "Memory allocation failed : %s\n", extra);
    else
        __xmlRaiseError(NULL, channel, data,
                        pctxt, NULL, XML_FROM_VALID, XML_ERR_NO_MEMORY,
                        XML_ERR_FATAL, NULL, 0, NULL, NULL, NULL, 0, 0,
                        "Memory allocation failed\n");
}