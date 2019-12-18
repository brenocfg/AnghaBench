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
typedef  int /*<<< orphan*/  xmlParserInputBuffer ;
typedef  int /*<<< orphan*/  xmlCharEncoding ;
struct TYPE_5__ {int compressed; int /*<<< orphan*/ * closecallback; int /*<<< orphan*/ * readcallback; void* context; int /*<<< orphan*/ * raw; int /*<<< orphan*/ * encoder; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * xmlBufCreateSize (int) ; 
 int /*<<< orphan*/ * xmlBufCreateStatic (void*,size_t) ; 
 int xmlDefaultBufferSize ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/ * xmlGetCharEncodingHandler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlIOErrMemory (char*) ; 
 scalar_t__ xmlMalloc (int) ; 

xmlParserInputBufferPtr
xmlParserInputBufferCreateStatic(const char *mem, int size,
                                 xmlCharEncoding enc) {
    xmlParserInputBufferPtr ret;

    if (size < 0) return(NULL);
    if (mem == NULL) return(NULL);

    ret = (xmlParserInputBufferPtr) xmlMalloc(sizeof(xmlParserInputBuffer));
    if (ret == NULL) {
	xmlIOErrMemory("creating input buffer");
	return(NULL);
    }
    memset(ret, 0, (size_t) sizeof(xmlParserInputBuffer));
    ret->buffer = xmlBufCreateStatic((void *)mem, (size_t) size);
    if (ret->buffer == NULL) {
        xmlFree(ret);
	return(NULL);
    }
    ret->encoder = xmlGetCharEncodingHandler(enc);
    if (ret->encoder != NULL)
        ret->raw = xmlBufCreateSize(2 * xmlDefaultBufferSize);
    else
        ret->raw = NULL;
    ret->compressed = -1;
    ret->context = (void *) mem;
    ret->readcallback = NULL;
    ret->closecallback = NULL;

    return(ret);
}