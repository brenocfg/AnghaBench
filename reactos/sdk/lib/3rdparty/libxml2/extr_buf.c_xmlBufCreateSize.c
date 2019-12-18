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
typedef  scalar_t__ xmlChar ;
typedef  TYPE_1__* xmlBufPtr ;
typedef  int /*<<< orphan*/  xmlBuf ;
struct TYPE_5__ {size_t size; int compat_size; int /*<<< orphan*/ * contentIO; scalar_t__* content; int /*<<< orphan*/  alloc; int /*<<< orphan*/ * buffer; scalar_t__ error; scalar_t__ use; scalar_t__ compat_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlBufMemoryError (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  xmlBufferAllocScheme ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 scalar_t__ xmlMalloc (int) ; 
 scalar_t__ xmlMallocAtomic (int) ; 

xmlBufPtr
xmlBufCreateSize(size_t size) {
    xmlBufPtr ret;

    ret = (xmlBufPtr) xmlMalloc(sizeof(xmlBuf));
    if (ret == NULL) {
	xmlBufMemoryError(NULL, "creating buffer");
        return(NULL);
    }
    ret->compat_use = 0;
    ret->use = 0;
    ret->error = 0;
    ret->buffer = NULL;
    ret->alloc = xmlBufferAllocScheme;
    ret->size = (size ? size+2 : 0);         /* +1 for ending null */
    ret->compat_size = (int) ret->size;
    if (ret->size){
        ret->content = (xmlChar *) xmlMallocAtomic(ret->size * sizeof(xmlChar));
        if (ret->content == NULL) {
	    xmlBufMemoryError(ret, "creating buffer");
            xmlFree(ret);
            return(NULL);
        }
        ret->content[0] = 0;
    } else
	ret->content = NULL;
    ret->contentIO = NULL;
    return(ret);
}