#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlBufferPtr ;
typedef  TYPE_2__* xmlBufPtr ;
typedef  int /*<<< orphan*/  xmlBuf ;
struct TYPE_6__ {int /*<<< orphan*/  contentIO; int /*<<< orphan*/  content; int /*<<< orphan*/  alloc; TYPE_1__* buffer; scalar_t__ error; int /*<<< orphan*/  compat_size; int /*<<< orphan*/  compat_use; int /*<<< orphan*/  size; int /*<<< orphan*/  use; } ;
struct TYPE_5__ {int /*<<< orphan*/  contentIO; int /*<<< orphan*/  content; int /*<<< orphan*/  alloc; int /*<<< orphan*/  size; int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlBufMemoryError (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ xmlMalloc (int) ; 

xmlBufPtr
xmlBufFromBuffer(xmlBufferPtr buffer) {
    xmlBufPtr ret;

    if (buffer == NULL)
        return(NULL);

    ret = (xmlBufPtr) xmlMalloc(sizeof(xmlBuf));
    if (ret == NULL) {
	xmlBufMemoryError(NULL, "creating buffer");
        return(NULL);
    }
    ret->use = buffer->use;
    ret->size = buffer->size;
    ret->compat_use = buffer->use;
    ret->compat_size = buffer->size;
    ret->error = 0;
    ret->buffer = buffer;
    ret->alloc = buffer->alloc;
    ret->content = buffer->content;
    ret->contentIO = buffer->contentIO;

    return(ret);
}