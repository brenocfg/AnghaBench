#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xmlBufferAllocationScheme ;
typedef  TYPE_2__* xmlBufPtr ;
struct TYPE_5__ {scalar_t__ error; scalar_t__ alloc; int /*<<< orphan*/  content; int /*<<< orphan*/  contentIO; TYPE_1__* buffer; } ;
struct TYPE_4__ {scalar_t__ alloc; } ;

/* Variables and functions */
 scalar_t__ XML_BUFFER_ALLOC_BOUNDED ; 
 scalar_t__ XML_BUFFER_ALLOC_DOUBLEIT ; 
 scalar_t__ XML_BUFFER_ALLOC_EXACT ; 
 scalar_t__ XML_BUFFER_ALLOC_HYBRID ; 
 scalar_t__ XML_BUFFER_ALLOC_IMMUTABLE ; 
 scalar_t__ XML_BUFFER_ALLOC_IO ; 

int
xmlBufSetAllocationScheme(xmlBufPtr buf,
                          xmlBufferAllocationScheme scheme) {
    if ((buf == NULL) || (buf->error != 0)) {
#ifdef DEBUG_BUFFER
        xmlGenericError(xmlGenericErrorContext,
		"xmlBufSetAllocationScheme: buf == NULL or in error\n");
#endif
        return(-1);
    }
    if ((buf->alloc == XML_BUFFER_ALLOC_IMMUTABLE) ||
        (buf->alloc == XML_BUFFER_ALLOC_IO))
        return(-1);
    if ((scheme == XML_BUFFER_ALLOC_DOUBLEIT) ||
        (scheme == XML_BUFFER_ALLOC_EXACT) ||
        (scheme == XML_BUFFER_ALLOC_HYBRID) ||
        (scheme == XML_BUFFER_ALLOC_IMMUTABLE) ||
	(scheme == XML_BUFFER_ALLOC_BOUNDED)) {
	buf->alloc = scheme;
        if (buf->buffer)
            buf->buffer->alloc = scheme;
        return(0);
    }
    /*
     * Switching a buffer ALLOC_IO has the side effect of initializing
     * the contentIO field with the current content
     */
    if (scheme == XML_BUFFER_ALLOC_IO) {
        buf->alloc = XML_BUFFER_ALLOC_IO;
        buf->contentIO = buf->content;
    }
    return(-1);
}