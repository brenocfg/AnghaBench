#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int avail_in; scalar_t__ next_in; } ;
typedef  TYPE_1__ z_stream ;
typedef  TYPE_2__* xmlParserInputBufferPtr ;
typedef  int /*<<< orphan*/  xmlCharEncoding ;
struct TYPE_8__ {scalar_t__ (* matchcallback ) (char const*) ;int /*<<< orphan*/  (* closecallback ) (void*) ;void* (* opencallback ) (char const*) ;int /*<<< orphan*/  readcallback; } ;
struct TYPE_7__ {int compressed; int /*<<< orphan*/  (* closecallback ) (void*) ;int /*<<< orphan*/  readcallback; void* context; } ;

/* Variables and functions */
 int __libxml2_xzcompressed (void*) ; 
 int /*<<< orphan*/  gzdirect (void*) ; 
 int gzread (void*,char*,int) ; 
 int /*<<< orphan*/  gzrewind (void*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ stub1 (char const*) ; 
 void* stub2 (char const*) ; 
 int /*<<< orphan*/  stub3 (void*) ; 
 TYPE_2__* xmlAllocParserInputBuffer (int /*<<< orphan*/ ) ; 
 void* xmlGzfileOpen (char const*) ; 
 scalar_t__ xmlInputCallbackInitialized ; 
 int xmlInputCallbackNr ; 
 TYPE_3__* xmlInputCallbackTable ; 
 int /*<<< orphan*/  xmlRegisterDefaultInputCallbacks () ; 
 void* xmlXzfileOpen (char const*) ; 

xmlParserInputBufferPtr
__xmlParserInputBufferCreateFilename(const char *URI, xmlCharEncoding enc) {
    xmlParserInputBufferPtr ret;
    int i = 0;
    void *context = NULL;

    if (xmlInputCallbackInitialized == 0)
	xmlRegisterDefaultInputCallbacks();

    if (URI == NULL) return(NULL);

    /*
     * Try to find one of the input accept method accepting that scheme
     * Go in reverse to give precedence to user defined handlers.
     */
    if (context == NULL) {
	for (i = xmlInputCallbackNr - 1;i >= 0;i--) {
	    if ((xmlInputCallbackTable[i].matchcallback != NULL) &&
		(xmlInputCallbackTable[i].matchcallback(URI) != 0)) {
		context = xmlInputCallbackTable[i].opencallback(URI);
		if (context != NULL) {
		    break;
		}
	    }
	}
    }
    if (context == NULL) {
	return(NULL);
    }

    /*
     * Allocate the Input buffer front-end.
     */
    ret = xmlAllocParserInputBuffer(enc);
    if (ret != NULL) {
	ret->context = context;
	ret->readcallback = xmlInputCallbackTable[i].readcallback;
	ret->closecallback = xmlInputCallbackTable[i].closecallback;
#ifdef LIBXML_ZLIB_ENABLED
	if ((xmlInputCallbackTable[i].opencallback == xmlGzfileOpen) &&
		(strcmp(URI, "-") != 0)) {
#if defined(ZLIB_VERNUM) && ZLIB_VERNUM >= 0x1230
            ret->compressed = !gzdirect(context);
#else
	    if (((z_stream *)context)->avail_in > 4) {
	        char *cptr, buff4[4];
		cptr = (char *) ((z_stream *)context)->next_in;
		if (gzread(context, buff4, 4) == 4) {
		    if (strncmp(buff4, cptr, 4) == 0)
		        ret->compressed = 0;
		    else
		        ret->compressed = 1;
		    gzrewind(context);
		}
	    }
#endif
	}
#endif
#ifdef LIBXML_LZMA_ENABLED
	if ((xmlInputCallbackTable[i].opencallback == xmlXzfileOpen) &&
		(strcmp(URI, "-") != 0)) {
            ret->compressed = __libxml2_xzcompressed(context);
	}
#endif
    }
    else
      xmlInputCallbackTable[i].closecallback (context);

    return(ret);
}