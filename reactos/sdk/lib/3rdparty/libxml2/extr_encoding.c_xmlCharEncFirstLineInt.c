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
struct TYPE_6__ {int size; int use; scalar_t__* content; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlBufferGrow (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xmlBufferShrink (TYPE_1__*,int) ; 
 int xmlEncInputChunk (int /*<<< orphan*/ *,scalar_t__*,int*,scalar_t__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 

int
xmlCharEncFirstLineInt(xmlCharEncodingHandler *handler, xmlBufferPtr out,
                       xmlBufferPtr in, int len) {
    int ret;
    int written;
    int toconv;

    if (handler == NULL) return(-1);
    if (out == NULL) return(-1);
    if (in == NULL) return(-1);

    /* calculate space available */
    written = out->size - out->use - 1; /* count '\0' */
    toconv = in->use;
    /*
     * echo '<?xml version="1.0" encoding="UCS4"?>' | wc -c => 38
     * 45 chars should be sufficient to reach the end of the encoding
     * declaration without going too far inside the document content.
     * on UTF-16 this means 90bytes, on UCS4 this means 180
     * The actual value depending on guessed encoding is passed as @len
     * if provided
     */
    if (len >= 0) {
        if (toconv > len)
            toconv = len;
    } else {
        if (toconv > 180)
            toconv = 180;
    }
    if (toconv * 2 >= written) {
        xmlBufferGrow(out, toconv * 2);
	written = out->size - out->use - 1;
    }

    ret = xmlEncInputChunk(handler, &out->content[out->use], &written,
                           in->content, &toconv, 0);
    xmlBufferShrink(in, toconv);
    out->use += written;
    out->content[out->use] = 0;
    if (ret == -1) ret = -3;

#ifdef DEBUG_ENCODING
    switch (ret) {
        case 0:
	    xmlGenericError(xmlGenericErrorContext,
		    "converted %d bytes to %d bytes of input\n",
	            toconv, written);
	    break;
        case -1:
	    xmlGenericError(xmlGenericErrorContext,"converted %d bytes to %d bytes of input, %d left\n",
	            toconv, written, in->use);
	    break;
        case -2:
	    xmlGenericError(xmlGenericErrorContext,
		    "input conversion failed due to input error\n");
	    break;
        case -3:
	    xmlGenericError(xmlGenericErrorContext,"converted %d bytes to %d bytes of input, %d left\n",
	            toconv, written, in->use);
	    break;
	default:
	    xmlGenericError(xmlGenericErrorContext,"Unknown input conversion failed %d\n", ret);
    }
#endif /* DEBUG_ENCODING */
    /*
     * Ignore when input buffer is not on a boundary
     */
    if (ret == -3) ret = 0;
    if (ret == -1) ret = 0;
    return(ret);
}