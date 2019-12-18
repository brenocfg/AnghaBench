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
typedef  TYPE_1__* xmlBufferPtr ;
struct TYPE_3__ {unsigned int use; scalar_t__ alloc; size_t size; scalar_t__* content; scalar_t__* contentIO; } ;

/* Variables and functions */
 scalar_t__ XML_BUFFER_ALLOC_IMMUTABLE ; 
 scalar_t__ XML_BUFFER_ALLOC_IO ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,unsigned int) ; 

int
xmlBufferShrink(xmlBufferPtr buf, unsigned int len) {
    if (buf == NULL) return(-1);
    if (len == 0) return(0);
    if (len > buf->use) return(-1);

    buf->use -= len;
    if ((buf->alloc == XML_BUFFER_ALLOC_IMMUTABLE) ||
        ((buf->alloc == XML_BUFFER_ALLOC_IO) && (buf->contentIO != NULL))) {
	/*
	 * we just move the content pointer, but also make sure
	 * the perceived buffer size has shrinked accordingly
	 */
        buf->content += len;
	buf->size -= len;

        /*
	 * sometimes though it maybe be better to really shrink
	 * on IO buffers
	 */
	if ((buf->alloc == XML_BUFFER_ALLOC_IO) && (buf->contentIO != NULL)) {
	    size_t start_buf = buf->content - buf->contentIO;
	    if (start_buf >= buf->size) {
		memmove(buf->contentIO, &buf->content[0], buf->use);
		buf->content = buf->contentIO;
		buf->content[buf->use] = 0;
		buf->size += start_buf;
	    }
	}
    } else {
	memmove(buf->content, &buf->content[len], buf->use);
	buf->content[buf->use] = 0;
    }
    return(len);
}