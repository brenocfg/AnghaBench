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
typedef  int /*<<< orphan*/  xmlParserInputPtr ;
typedef  int /*<<< orphan*/  xmlParserCtxtPtr ;

/* Variables and functions */

xmlParserInputPtr
xmlCheckHTTPInput(xmlParserCtxtPtr ctxt, xmlParserInputPtr ret) {
#ifdef LIBXML_HTTP_ENABLED
    if ((ret != NULL) && (ret->buf != NULL) &&
        (ret->buf->readcallback == xmlIOHTTPRead) &&
        (ret->buf->context != NULL)) {
        const char *encoding;
        const char *redir;
        const char *mime;
        int code;

        code = xmlNanoHTTPReturnCode(ret->buf->context);
        if (code >= 400) {
            /* fatal error */
	    if (ret->filename != NULL)
		__xmlLoaderErr(ctxt, "failed to load HTTP resource \"%s\"\n",
                         (const char *) ret->filename);
	    else
		__xmlLoaderErr(ctxt, "failed to load HTTP resource\n", NULL);
            xmlFreeInputStream(ret);
            ret = NULL;
        } else {

            mime = xmlNanoHTTPMimeType(ret->buf->context);
            if ((xmlStrstr(BAD_CAST mime, BAD_CAST "/xml")) ||
                (xmlStrstr(BAD_CAST mime, BAD_CAST "+xml"))) {
                encoding = xmlNanoHTTPEncoding(ret->buf->context);
                if (encoding != NULL) {
                    xmlCharEncodingHandlerPtr handler;

                    handler = xmlFindCharEncodingHandler(encoding);
                    if (handler != NULL) {
                        xmlSwitchInputEncoding(ctxt, ret, handler);
                    } else {
                        __xmlErrEncoding(ctxt, XML_ERR_UNKNOWN_ENCODING,
                                         "Unknown encoding %s",
                                         BAD_CAST encoding, NULL);
                    }
                    if (ret->encoding == NULL)
                        ret->encoding = xmlStrdup(BAD_CAST encoding);
                }
#if 0
            } else if (xmlStrstr(BAD_CAST mime, BAD_CAST "html")) {
#endif
            }
            redir = xmlNanoHTTPRedir(ret->buf->context);
            if (redir != NULL) {
                if (ret->filename != NULL)
                    xmlFree((xmlChar *) ret->filename);
                if (ret->directory != NULL) {
                    xmlFree((xmlChar *) ret->directory);
                    ret->directory = NULL;
                }
                ret->filename =
                    (char *) xmlStrdup((const xmlChar *) redir);
            }
        }
    }
#endif
    return(ret);
}