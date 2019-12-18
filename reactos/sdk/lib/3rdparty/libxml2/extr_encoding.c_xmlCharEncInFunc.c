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
typedef  TYPE_1__* xmlBufferPtr ;
struct TYPE_6__ {int use; int size; int* content; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_I18N_CONV_FAILED ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  xmlBufferGrow (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xmlBufferShrink (TYPE_1__*,int) ; 
 int xmlEncInputChunk (int /*<<< orphan*/ *,int*,int*,int*,int*,int) ; 
 int /*<<< orphan*/  xmlEncodingErr (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 

int
xmlCharEncInFunc(xmlCharEncodingHandler * handler, xmlBufferPtr out,
                 xmlBufferPtr in)
{
    int ret;
    int written;
    int toconv;

    if (handler == NULL)
        return (-1);
    if (out == NULL)
        return (-1);
    if (in == NULL)
        return (-1);

    toconv = in->use;
    if (toconv == 0)
        return (0);
    written = out->size - out->use -1; /* count '\0' */
    if (toconv * 2 >= written) {
        xmlBufferGrow(out, out->size + toconv * 2);
        written = out->size - out->use - 1;
    }
    ret = xmlEncInputChunk(handler, &out->content[out->use], &written,
                           in->content, &toconv, 1);
    xmlBufferShrink(in, toconv);
    out->use += written;
    out->content[out->use] = 0;
    if (ret == -1)
        ret = -3;

    switch (ret) {
        case 0:
#ifdef DEBUG_ENCODING
            xmlGenericError(xmlGenericErrorContext,
                            "converted %d bytes to %d bytes of input\n",
                            toconv, written);
#endif
            break;
        case -1:
#ifdef DEBUG_ENCODING
            xmlGenericError(xmlGenericErrorContext,
                         "converted %d bytes to %d bytes of input, %d left\n",
                            toconv, written, in->use);
#endif
            break;
        case -3:
#ifdef DEBUG_ENCODING
            xmlGenericError(xmlGenericErrorContext,
                        "converted %d bytes to %d bytes of input, %d left\n",
                            toconv, written, in->use);
#endif
            break;
        case -2: {
            char buf[50];

	    snprintf(&buf[0], 49, "0x%02X 0x%02X 0x%02X 0x%02X",
		     in->content[0], in->content[1],
		     in->content[2], in->content[3]);
	    buf[49] = 0;
	    xmlEncodingErr(XML_I18N_CONV_FAILED,
		    "input conversion failed due to input error, bytes %s\n",
		           buf);
        }
    }
    /*
     * Ignore when input buffer is not on a boundary
     */
    if (ret == -3)
        ret = 0;
    return (written? written : ret);
}