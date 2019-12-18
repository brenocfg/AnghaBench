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
struct TYPE_5__ {struct TYPE_5__* name; int /*<<< orphan*/ * uconv_in; int /*<<< orphan*/ * uconv_out; int /*<<< orphan*/ * iconv_in; int /*<<< orphan*/ * iconv_out; } ;
typedef  TYPE_1__ xmlCharEncodingHandler ;

/* Variables and functions */
 int /*<<< orphan*/  closeIcuConverter (int /*<<< orphan*/ *) ; 
 TYPE_1__** handlers ; 
 scalar_t__ iconv_close (int /*<<< orphan*/ *) ; 
 int nbCharEncodingHandler ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 

int
xmlCharEncCloseFunc(xmlCharEncodingHandler *handler) {
    int ret = 0;
    int tofree = 0;
    int i, handler_in_list = 0;

    if (handler == NULL) return(-1);
    if (handler->name == NULL) return(-1);
    if (handlers != NULL) {
        for (i = 0;i < nbCharEncodingHandler; i++) {
            if (handler == handlers[i]) {
	        handler_in_list = 1;
		break;
	    }
	}
    }
#ifdef LIBXML_ICONV_ENABLED
    /*
     * Iconv handlers can be used only once, free the whole block.
     * and the associated icon resources.
     */
    if ((handler_in_list == 0) &&
        ((handler->iconv_out != NULL) || (handler->iconv_in != NULL))) {
        tofree = 1;
	if (handler->iconv_out != NULL) {
	    if (iconv_close(handler->iconv_out))
		ret = -1;
	    handler->iconv_out = NULL;
	}
	if (handler->iconv_in != NULL) {
	    if (iconv_close(handler->iconv_in))
		ret = -1;
	    handler->iconv_in = NULL;
	}
    }
#endif /* LIBXML_ICONV_ENABLED */
#ifdef LIBXML_ICU_ENABLED
    if ((handler_in_list == 0) &&
        ((handler->uconv_out != NULL) || (handler->uconv_in != NULL))) {
        tofree = 1;
	if (handler->uconv_out != NULL) {
	    closeIcuConverter(handler->uconv_out);
	    handler->uconv_out = NULL;
	}
	if (handler->uconv_in != NULL) {
	    closeIcuConverter(handler->uconv_in);
	    handler->uconv_in = NULL;
	}
    }
#endif
    if (tofree) {
        /* free up only dynamic handlers iconv/uconv */
        if (handler->name != NULL)
            xmlFree(handler->name);
        handler->name = NULL;
        xmlFree(handler);
    }
#ifdef DEBUG_ENCODING
    if (ret)
        xmlGenericError(xmlGenericErrorContext,
		"failed to close the encoding handler\n");
    else
        xmlGenericError(xmlGenericErrorContext,
		"closed the encoding handler\n");
#endif

    return(ret);
}