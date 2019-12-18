#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlCharEncodingHandler ;
typedef  int xmlChar ;
typedef  TYPE_1__* xmlBufferPtr ;
typedef  int /*<<< orphan*/  charref ;
struct TYPE_6__ {int size; int use; int* content; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_BUFFER_ALLOC_IMMUTABLE ; 
 int /*<<< orphan*/  XML_I18N_CONV_FAILED ; 
 int /*<<< orphan*/  XML_I18N_NO_OUTPUT ; 
 int snprintf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/  xmlBufferGrow (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xmlBufferShrink (TYPE_1__*,int) ; 
 int xmlEncOutputChunk (int /*<<< orphan*/ *,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  xmlEncodingErr (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int xmlGetUTF8Char (int const*,int*) ; 

int
xmlCharEncOutFunc(xmlCharEncodingHandler *handler, xmlBufferPtr out,
                  xmlBufferPtr in) {
    int ret;
    int written;
    int writtentot = 0;
    int toconv;
    int output = 0;

    if (handler == NULL) return(-1);
    if (out == NULL) return(-1);

retry:

    written = out->size - out->use;

    if (written > 0)
	written--; /* Gennady: count '/0' */

    /*
     * First specific handling of in = NULL, i.e. the initialization call
     */
    if (in == NULL) {
        toconv = 0;
        /* TODO: Check return value. */
        xmlEncOutputChunk(handler, &out->content[out->use], &written,
                          NULL, &toconv);
        out->use += written;
        out->content[out->use] = 0;
#ifdef DEBUG_ENCODING
	xmlGenericError(xmlGenericErrorContext,
		"initialized encoder\n");
#endif
        return(0);
    }

    /*
     * Conversion itself.
     */
    toconv = in->use;
    if (toconv == 0)
	return(0);
    if (toconv * 4 >= written) {
        xmlBufferGrow(out, toconv * 4);
	written = out->size - out->use - 1;
    }
    ret = xmlEncOutputChunk(handler, &out->content[out->use], &written,
                            in->content, &toconv);
    xmlBufferShrink(in, toconv);
    out->use += written;
    writtentot += written;
    out->content[out->use] = 0;
    if (ret == -1) {
        if (written > 0) {
            /* Can be a limitation of iconv or uconv */
            goto retry;
        }
        ret = -3;
    }

    if (ret >= 0) output += ret;

    /*
     * Attempt to handle error cases
     */
    switch (ret) {
        case 0:
#ifdef DEBUG_ENCODING
	    xmlGenericError(xmlGenericErrorContext,
		    "converted %d bytes to %d bytes of output\n",
	            toconv, written);
#endif
	    break;
        case -1:
#ifdef DEBUG_ENCODING
	    xmlGenericError(xmlGenericErrorContext,
		    "output conversion failed by lack of space\n");
#endif
	    break;
        case -3:
#ifdef DEBUG_ENCODING
	    xmlGenericError(xmlGenericErrorContext,"converted %d bytes to %d bytes of output %d left\n",
	            toconv, written, in->use);
#endif
	    break;
        case -4:
	    xmlEncodingErr(XML_I18N_NO_OUTPUT,
		           "xmlCharEncOutFunc: no output function !\n", NULL);
	    ret = -1;
            break;
        case -2: {
	    xmlChar charref[20];
	    int len = in->use;
	    const xmlChar *utf = (const xmlChar *) in->content;
	    int cur, charrefLen;

	    cur = xmlGetUTF8Char(utf, &len);
	    if (cur <= 0)
                break;

#ifdef DEBUG_ENCODING
            xmlGenericError(xmlGenericErrorContext,
                    "handling output conversion error\n");
            xmlGenericError(xmlGenericErrorContext,
                    "Bytes: 0x%02X 0x%02X 0x%02X 0x%02X\n",
                    in->content[0], in->content[1],
                    in->content[2], in->content[3]);
#endif
            /*
             * Removes the UTF8 sequence, and replace it by a charref
             * and continue the transcoding phase, hoping the error
             * did not mangle the encoder state.
             */
            charrefLen = snprintf((char *) &charref[0], sizeof(charref),
                             "&#%d;", cur);
            xmlBufferShrink(in, len);
            xmlBufferGrow(out, charrefLen * 4);
	    written = out->size - out->use - 1;
            toconv = charrefLen;
            ret = xmlEncOutputChunk(handler, &out->content[out->use], &written,
                                    charref, &toconv);

	    if ((ret < 0) || (toconv != charrefLen)) {
		char buf[50];

		snprintf(&buf[0], 49, "0x%02X 0x%02X 0x%02X 0x%02X",
			 in->content[0], in->content[1],
			 in->content[2], in->content[3]);
		buf[49] = 0;
		xmlEncodingErr(XML_I18N_CONV_FAILED,
		    "output conversion failed due to conv error, bytes %s\n",
			       buf);
		if (in->alloc != XML_BUFFER_ALLOC_IMMUTABLE)
		    in->content[0] = ' ';
	        break;
	    }

            out->use += written;
            writtentot += written;
            out->content[out->use] = 0;
            goto retry;
	}
    }
    return(ret);
}