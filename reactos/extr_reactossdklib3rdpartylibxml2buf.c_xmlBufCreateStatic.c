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
typedef  int /*<<< orphan*/  xmlChar ;
typedef  TYPE_1__* xmlBufPtr ;
typedef  int /*<<< orphan*/  xmlBuf ;
struct TYPE_3__ {size_t compat_use; size_t compat_size; size_t use; size_t size; int /*<<< orphan*/ * buffer; scalar_t__ error; int /*<<< orphan*/ * content; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 size_t INT_MAX ; 
 int /*<<< orphan*/  XML_BUFFER_ALLOC_IMMUTABLE ; 
 int /*<<< orphan*/  xmlBufMemoryError (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ xmlMalloc (int) ; 

xmlBufPtr
xmlBufCreateStatic(void *mem, size_t size) {
    xmlBufPtr ret;

    if (mem == NULL)
        return(NULL);

    ret = (xmlBufPtr) xmlMalloc(sizeof(xmlBuf));
    if (ret == NULL) {
	xmlBufMemoryError(NULL, "creating buffer");
        return(NULL);
    }
    if (size < INT_MAX) {
        ret->compat_use = size;
        ret->compat_size = size;
    } else {
        ret->compat_use = INT_MAX;
        ret->compat_size = INT_MAX;
    }
    ret->use = size;
    ret->size = size;
    ret->alloc = XML_BUFFER_ALLOC_IMMUTABLE;
    ret->content = (xmlChar *) mem;
    ret->error = 0;
    ret->buffer = NULL;
    return(ret);
}