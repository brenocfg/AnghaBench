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
struct TYPE_3__ {int (* input ) (unsigned char*,int*,unsigned char const*,int*) ;int /*<<< orphan*/ * uconv_in; int /*<<< orphan*/ * iconv_in; } ;
typedef  TYPE_1__ xmlCharEncodingHandler ;

/* Variables and functions */
 int stub1 (unsigned char*,int*,unsigned char const*,int*) ; 
 int xmlIconvWrapper (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char const*,int*) ; 
 int xmlUconvWrapper (int /*<<< orphan*/ *,int,unsigned char*,int*,unsigned char const*,int*,int) ; 

__attribute__((used)) static int
xmlEncInputChunk(xmlCharEncodingHandler *handler, unsigned char *out,
                 int *outlen, const unsigned char *in, int *inlen, int flush) {
    int ret;
    (void)flush;

    if (handler->input != NULL) {
        ret = handler->input(out, outlen, in, inlen);
    }
#ifdef LIBXML_ICONV_ENABLED
    else if (handler->iconv_in != NULL) {
        ret = xmlIconvWrapper(handler->iconv_in, out, outlen, in, inlen);
    }
#endif /* LIBXML_ICONV_ENABLED */
#ifdef LIBXML_ICU_ENABLED
    else if (handler->uconv_in != NULL) {
        ret = xmlUconvWrapper(handler->uconv_in, 1, out, outlen, in, inlen,
                              flush);
    }
#endif /* LIBXML_ICU_ENABLED */
    else {
        *outlen = 0;
        *inlen = 0;
        ret = -2;
    }

    return(ret);
}