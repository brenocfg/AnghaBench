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
struct TYPE_3__ {scalar_t__ alloc; scalar_t__ compat_size; scalar_t__ compat_use; scalar_t__ use; scalar_t__ size; int /*<<< orphan*/ * content; scalar_t__ error; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 scalar_t__ XML_BUFFER_ALLOC_IMMUTABLE ; 

xmlChar *
xmlBufDetach(xmlBufPtr buf) {
    xmlChar *ret;

    if (buf == NULL)
        return(NULL);
    if (buf->alloc == XML_BUFFER_ALLOC_IMMUTABLE)
        return(NULL);
    if (buf->buffer != NULL)
        return(NULL);
    if (buf->error)
        return(NULL);

    ret = buf->content;
    buf->content = NULL;
    buf->size = 0;
    buf->use = 0;
    buf->compat_use = 0;
    buf->compat_size = 0;

    return ret;
}