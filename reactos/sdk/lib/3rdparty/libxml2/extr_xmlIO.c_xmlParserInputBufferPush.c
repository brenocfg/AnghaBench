#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserInputBufferPtr ;
typedef  int /*<<< orphan*/  const xmlChar ;
struct TYPE_4__ {int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * raw; int /*<<< orphan*/  rawconsumed; scalar_t__ error; int /*<<< orphan*/ * encoder; } ;

/* Variables and functions */
 scalar_t__ XML_IO_ENCODER ; 
 int xmlBufAdd (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * xmlBufCreate () ; 
 int /*<<< orphan*/  xmlBufLength (int /*<<< orphan*/ *) ; 
 unsigned int xmlBufUse (int /*<<< orphan*/ *) ; 
 int xmlCharEncInput (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int /*<<< orphan*/  xmlIOErr (scalar_t__,int /*<<< orphan*/ *) ; 

int
xmlParserInputBufferPush(xmlParserInputBufferPtr in,
	                 int len, const char *buf) {
    int nbchars = 0;
    int ret;

    if (len < 0) return(0);
    if ((in == NULL) || (in->error)) return(-1);
    if (in->encoder != NULL) {
        unsigned int use;

        /*
	 * Store the data in the incoming raw buffer
	 */
        if (in->raw == NULL) {
	    in->raw = xmlBufCreate();
	}
	ret = xmlBufAdd(in->raw, (const xmlChar *) buf, len);
	if (ret != 0)
	    return(-1);

	/*
	 * convert as much as possible to the parser reading buffer.
	 */
	use = xmlBufUse(in->raw);
	nbchars = xmlCharEncInput(in, 1);
	if (nbchars < 0) {
	    xmlIOErr(XML_IO_ENCODER, NULL);
	    in->error = XML_IO_ENCODER;
	    return(-1);
	}
	in->rawconsumed += (use - xmlBufUse(in->raw));
    } else {
	nbchars = len;
        ret = xmlBufAdd(in->buffer, (xmlChar *) buf, nbchars);
	if (ret != 0)
	    return(-1);
    }
#ifdef DEBUG_INPUT
    xmlGenericError(xmlGenericErrorContext,
	    "I/O: pushed %d chars, buffer %d/%d\n",
            nbchars, xmlBufUse(in->buffer), xmlBufLength(in->buffer));
#endif
    return(nbchars);
}