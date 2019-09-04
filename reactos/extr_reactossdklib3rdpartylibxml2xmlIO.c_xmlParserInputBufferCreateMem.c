#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserInputBufferPtr ;
typedef  int /*<<< orphan*/  xmlCharEncoding ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_5__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/ * closecallback; int /*<<< orphan*/  readcallback; void* context; } ;

/* Variables and functions */
 TYPE_1__* xmlAllocParserInputBuffer (int /*<<< orphan*/ ) ; 
 int xmlBufAdd (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlInputReadCallbackNop ; 

xmlParserInputBufferPtr
xmlParserInputBufferCreateMem(const char *mem, int size, xmlCharEncoding enc) {
    xmlParserInputBufferPtr ret;
    int errcode;

    if (size < 0) return(NULL);
    if (mem == NULL) return(NULL);

    ret = xmlAllocParserInputBuffer(enc);
    if (ret != NULL) {
        ret->context = (void *) mem;
	ret->readcallback = xmlInputReadCallbackNop;
	ret->closecallback = NULL;
	errcode = xmlBufAdd(ret->buffer, (const xmlChar *) mem, size);
	if (errcode != 0) {
	    xmlFree(ret);
	    return(NULL);
	}
    }

    return(ret);
}