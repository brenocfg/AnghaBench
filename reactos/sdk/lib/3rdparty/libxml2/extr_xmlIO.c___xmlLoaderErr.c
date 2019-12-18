#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xmlStructuredErrorFunc ;
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlGenericErrorFunc ;
typedef  int /*<<< orphan*/  xmlErrorLevel ;
struct TYPE_5__ {scalar_t__ disableSAX; scalar_t__ instate; void* userData; TYPE_1__* sax; scalar_t__ validate; } ;
struct TYPE_4__ {scalar_t__ initialized; int /*<<< orphan*/ * serror; int /*<<< orphan*/ * warning; int /*<<< orphan*/ * error; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_ERR_ERROR ; 
 int /*<<< orphan*/  XML_ERR_WARNING ; 
 int /*<<< orphan*/  XML_FROM_IO ; 
 int /*<<< orphan*/  XML_IO_LOAD_ERROR ; 
 scalar_t__ XML_PARSER_EOF ; 
 scalar_t__ XML_SAX2_MAGIC ; 
 int /*<<< orphan*/  __xmlRaiseError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 

void
__xmlLoaderErr(void *ctx, const char *msg, const char *filename)
{
    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    xmlStructuredErrorFunc schannel = NULL;
    xmlGenericErrorFunc channel = NULL;
    void *data = NULL;
    xmlErrorLevel level = XML_ERR_ERROR;

    if ((ctxt != NULL) && (ctxt->disableSAX != 0) &&
        (ctxt->instate == XML_PARSER_EOF))
	return;
    if ((ctxt != NULL) && (ctxt->sax != NULL)) {
        if (ctxt->validate) {
	    channel = ctxt->sax->error;
	    level = XML_ERR_ERROR;
	} else {
	    channel = ctxt->sax->warning;
	    level = XML_ERR_WARNING;
	}
	if (ctxt->sax->initialized == XML_SAX2_MAGIC)
	    schannel = ctxt->sax->serror;
	data = ctxt->userData;
    }
    __xmlRaiseError(schannel, channel, data, ctxt, NULL, XML_FROM_IO,
                    XML_IO_LOAD_ERROR, level, NULL, 0,
		    filename, NULL, NULL, 0, 0,
		    msg, filename);

}