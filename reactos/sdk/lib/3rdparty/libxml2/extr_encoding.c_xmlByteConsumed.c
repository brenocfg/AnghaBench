#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserInputPtr ;
typedef  TYPE_3__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlCharEncodingHandler ;
struct TYPE_7__ {TYPE_2__* input; } ;
struct TYPE_6__ {unsigned char const* end; unsigned char const* cur; long consumed; unsigned char const* base; TYPE_1__* buf; } ;
struct TYPE_5__ {unsigned int rawconsumed; int /*<<< orphan*/ * encoder; } ;

/* Variables and functions */
 int xmlEncOutputChunk (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char const*,int*) ; 

long
xmlByteConsumed(xmlParserCtxtPtr ctxt) {
    xmlParserInputPtr in;

    if (ctxt == NULL) return(-1);
    in = ctxt->input;
    if (in == NULL)  return(-1);
    if ((in->buf != NULL) && (in->buf->encoder != NULL)) {
        unsigned int unused = 0;
	xmlCharEncodingHandler * handler = in->buf->encoder;
        /*
	 * Encoding conversion, compute the number of unused original
	 * bytes from the input not consumed and substract that from
	 * the raw consumed value, this is not a cheap operation
	 */
        if (in->end - in->cur > 0) {
	    unsigned char convbuf[32000];
	    const unsigned char *cur = (const unsigned char *)in->cur;
	    int toconv = in->end - in->cur, written = 32000;

	    int ret;

            do {
                toconv = in->end - cur;
                written = 32000;
                ret = xmlEncOutputChunk(handler, &convbuf[0], &written,
                                        cur, &toconv);
                if (ret < 0) {
                    if (written > 0)
                        ret = -2;
                    else
                        return(-1);
                }
                unused += written;
                cur += toconv;
            } while (ret == -2);
	}
	if (in->buf->rawconsumed < unused)
	    return(-1);
	return(in->buf->rawconsumed - unused);
    }
    return(in->consumed + (in->cur - in->base));
}