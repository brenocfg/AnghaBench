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
typedef  TYPE_1__* xmlBufferPtr ;
struct TYPE_3__ {scalar_t__ alloc; unsigned int use; unsigned int size; int /*<<< orphan*/ * content; int /*<<< orphan*/ * contentIO; } ;

/* Variables and functions */
 scalar_t__ XML_BUFFER_ALLOC_IMMUTABLE ; 
 scalar_t__ XML_BUFFER_ALLOC_IO ; 
 scalar_t__ xmlRealloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xmlTreeErrMemory (char*) ; 

int
xmlBufferGrow(xmlBufferPtr buf, unsigned int len) {
    int size;
    xmlChar *newbuf;

    if (buf == NULL) return(-1);

    if (buf->alloc == XML_BUFFER_ALLOC_IMMUTABLE) return(0);
    if (len + buf->use < buf->size) return(0);

    /*
     * Windows has a BIG problem on realloc timing, so we try to double
     * the buffer size (if that's enough) (bug 146697)
     * Apparently BSD too, and it's probably best for linux too
     * On an embedded system this may be something to change
     */
#if 1
    if (buf->size > len)
        size = buf->size * 2;
    else
        size = buf->use + len + 100;
#else
    size = buf->use + len + 100;
#endif

    if ((buf->alloc == XML_BUFFER_ALLOC_IO) && (buf->contentIO != NULL)) {
        size_t start_buf = buf->content - buf->contentIO;

	newbuf = (xmlChar *) xmlRealloc(buf->contentIO, start_buf + size);
	if (newbuf == NULL) {
	    xmlTreeErrMemory("growing buffer");
	    return(-1);
	}
	buf->contentIO = newbuf;
	buf->content = newbuf + start_buf;
    } else {
	newbuf = (xmlChar *) xmlRealloc(buf->content, size);
	if (newbuf == NULL) {
	    xmlTreeErrMemory("growing buffer");
	    return(-1);
	}
	buf->content = newbuf;
    }
    buf->size = size;
    return(buf->size - buf->use);
}