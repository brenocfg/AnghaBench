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
struct TYPE_3__ {int (* output ) (unsigned char*,int*,unsigned char const*,int*) ;int /*<<< orphan*/ * uconv_out; int /*<<< orphan*/ * iconv_out; } ;
typedef  TYPE_1__ xmlCharEncodingHandler ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int stub1 (unsigned char*,int*,unsigned char const*,int*) ; 
 int xmlIconvWrapper (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char const*,int*) ; 
 int xmlUconvWrapper (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int*,unsigned char const*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xmlEncOutputChunk(xmlCharEncodingHandler *handler, unsigned char *out,
                  int *outlen, const unsigned char *in, int *inlen) {
    int ret;

    if (handler->output != NULL) {
        ret = handler->output(out, outlen, in, inlen);
    }
#ifdef LIBXML_ICONV_ENABLED
    else if (handler->iconv_out != NULL) {
        ret = xmlIconvWrapper(handler->iconv_out, out, outlen, in, inlen);
    }
#endif /* LIBXML_ICONV_ENABLED */
#ifdef LIBXML_ICU_ENABLED
    else if (handler->uconv_out != NULL) {
        ret = xmlUconvWrapper(handler->uconv_out, 0, out, outlen, in, inlen,
                              TRUE);
    }
#endif /* LIBXML_ICU_ENABLED */
    else {
        *outlen = 0;
        *inlen = 0;
        ret = -4;
    }

    return(ret);
}