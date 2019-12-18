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
typedef  TYPE_1__* xmlParserInputBufferPtr ;
typedef  int xmlChar ;
typedef  int /*<<< orphan*/ * xmlBufPtr ;
struct TYPE_3__ {int /*<<< orphan*/ * encoder; int /*<<< orphan*/ * raw; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_I18N_CONV_FAILED ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int const,int const,int const,int const) ; 
 int /*<<< orphan*/  xmlBufAddLen (int /*<<< orphan*/ *,int) ; 
 int xmlBufAvail (int /*<<< orphan*/ *) ; 
 int* xmlBufContent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlBufEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlBufGrow (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  xmlBufShrink (int /*<<< orphan*/ *,int) ; 
 size_t xmlBufUse (int /*<<< orphan*/ *) ; 
 int xmlEncInputChunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlEncodingErr (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 

int
xmlCharEncFirstLineInput(xmlParserInputBufferPtr input, int len)
{
    int ret;
    size_t written;
    size_t toconv;
    int c_in;
    int c_out;
    xmlBufPtr in;
    xmlBufPtr out;

    if ((input == NULL) || (input->encoder == NULL) ||
        (input->buffer == NULL) || (input->raw == NULL))
        return (-1);
    out = input->buffer;
    in = input->raw;

    toconv = xmlBufUse(in);
    if (toconv == 0)
        return (0);
    written = xmlBufAvail(out) - 1; /* count '\0' */
    /*
     * echo '<?xml version="1.0" encoding="UCS4"?>' | wc -c => 38
     * 45 chars should be sufficient to reach the end of the encoding
     * declaration without going too far inside the document content.
     * on UTF-16 this means 90bytes, on UCS4 this means 180
     * The actual value depending on guessed encoding is passed as @len
     * if provided
     */
    if (len >= 0) {
        if (toconv > (unsigned int) len)
            toconv = len;
    } else {
        if (toconv > 180)
            toconv = 180;
    }
    if (toconv * 2 >= written) {
        xmlBufGrow(out, toconv * 2);
        written = xmlBufAvail(out) - 1;
    }
    if (written > 360)
        written = 360;

    c_in = toconv;
    c_out = written;
    ret = xmlEncInputChunk(input->encoder, xmlBufEnd(out), &c_out,
                           xmlBufContent(in), &c_in, 0);
    xmlBufShrink(in, c_in);
    xmlBufAddLen(out, c_out);
    if (ret == -1)
        ret = -3;

    switch (ret) {
        case 0:
#ifdef DEBUG_ENCODING
            xmlGenericError(xmlGenericErrorContext,
                            "converted %d bytes to %d bytes of input\n",
                            c_in, c_out);
#endif
            break;
        case -1:
#ifdef DEBUG_ENCODING
            xmlGenericError(xmlGenericErrorContext,
                         "converted %d bytes to %d bytes of input, %d left\n",
                            c_in, c_out, (int)xmlBufUse(in));
#endif
            break;
        case -3:
#ifdef DEBUG_ENCODING
            xmlGenericError(xmlGenericErrorContext,
                        "converted %d bytes to %d bytes of input, %d left\n",
                            c_in, c_out, (int)xmlBufUse(in));
#endif
            break;
        case -2: {
            char buf[50];
            const xmlChar *content = xmlBufContent(in);

	    snprintf(&buf[0], 49, "0x%02X 0x%02X 0x%02X 0x%02X",
		     content[0], content[1],
		     content[2], content[3]);
	    buf[49] = 0;
	    xmlEncodingErr(XML_I18N_CONV_FAILED,
		    "input conversion failed due to input error, bytes %s\n",
		           buf);
        }
    }
    /*
     * Ignore when input buffer is not on a boundary
     */
    if (ret == -3) ret = 0;
    if (ret == -1) ret = 0;
    return(ret);
}