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
typedef  scalar_t__ xmlChar ;
typedef  TYPE_1__* xmlBufferPtr ;
struct TYPE_3__ {int alloc; unsigned int size; size_t use; scalar_t__* content; scalar_t__* contentIO; } ;

/* Variables and functions */
 size_t BASE_BUFFER_SIZE ; 
 int UINT_MAX ; 
#define  XML_BUFFER_ALLOC_DOUBLEIT 131 
#define  XML_BUFFER_ALLOC_EXACT 130 
#define  XML_BUFFER_ALLOC_HYBRID 129 
 int XML_BUFFER_ALLOC_IMMUTABLE ; 
#define  XML_BUFFER_ALLOC_IO 128 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  xmlFree (scalar_t__*) ; 
 scalar_t__ xmlMallocAtomic (unsigned int) ; 
 scalar_t__ xmlRealloc (scalar_t__*,unsigned int) ; 
 int /*<<< orphan*/  xmlTreeErrMemory (char*) ; 

int
xmlBufferResize(xmlBufferPtr buf, unsigned int size)
{
    unsigned int newSize;
    xmlChar* rebuf = NULL;
    size_t start_buf;

    if (buf == NULL)
        return(0);

    if (buf->alloc == XML_BUFFER_ALLOC_IMMUTABLE) return(0);

    /* Don't resize if we don't have to */
    if (size < buf->size)
        return 1;

    /* figure out new size */
    switch (buf->alloc){
	case XML_BUFFER_ALLOC_IO:
	case XML_BUFFER_ALLOC_DOUBLEIT:
	    /*take care of empty case*/
	    newSize = (buf->size ? buf->size*2 : size + 10);
	    while (size > newSize) {
	        if (newSize > UINT_MAX / 2) {
	            xmlTreeErrMemory("growing buffer");
	            return 0;
	        }
	        newSize *= 2;
	    }
	    break;
	case XML_BUFFER_ALLOC_EXACT:
	    newSize = size+10;
	    break;
        case XML_BUFFER_ALLOC_HYBRID:
            if (buf->use < BASE_BUFFER_SIZE)
                newSize = size;
            else {
                newSize = buf->size * 2;
                while (size > newSize) {
                    if (newSize > UINT_MAX / 2) {
                        xmlTreeErrMemory("growing buffer");
                        return 0;
                    }
                    newSize *= 2;
                }
            }
            break;

	default:
	    newSize = size+10;
	    break;
    }

    if ((buf->alloc == XML_BUFFER_ALLOC_IO) && (buf->contentIO != NULL)) {
        start_buf = buf->content - buf->contentIO;

        if (start_buf > newSize) {
	    /* move data back to start */
	    memmove(buf->contentIO, buf->content, buf->use);
	    buf->content = buf->contentIO;
	    buf->content[buf->use] = 0;
	    buf->size += start_buf;
	} else {
	    rebuf = (xmlChar *) xmlRealloc(buf->contentIO, start_buf + newSize);
	    if (rebuf == NULL) {
		xmlTreeErrMemory("growing buffer");
		return 0;
	    }
	    buf->contentIO = rebuf;
	    buf->content = rebuf + start_buf;
	}
    } else {
	if (buf->content == NULL) {
	    rebuf = (xmlChar *) xmlMallocAtomic(newSize);
	} else if (buf->size - buf->use < 100) {
	    rebuf = (xmlChar *) xmlRealloc(buf->content, newSize);
        } else {
	    /*
	     * if we are reallocating a buffer far from being full, it's
	     * better to make a new allocation and copy only the used range
	     * and free the old one.
	     */
	    rebuf = (xmlChar *) xmlMallocAtomic(newSize);
	    if (rebuf != NULL) {
		memcpy(rebuf, buf->content, buf->use);
		xmlFree(buf->content);
		rebuf[buf->use] = 0;
	    }
	}
	if (rebuf == NULL) {
	    xmlTreeErrMemory("growing buffer");
	    return 0;
	}
	buf->content = rebuf;
    }
    buf->size = newSize;

    return 1;
}