#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlBufferPtr ;
struct TYPE_4__ {scalar_t__ alloc; struct TYPE_4__* content; struct TYPE_4__* contentIO; } ;

/* Variables and functions */
 scalar_t__ XML_BUFFER_ALLOC_IMMUTABLE ; 
 scalar_t__ XML_BUFFER_ALLOC_IO ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 

void
xmlBufferFree(xmlBufferPtr buf) {
    if (buf == NULL) {
#ifdef DEBUG_BUFFER
        xmlGenericError(xmlGenericErrorContext,
		"xmlBufferFree: buf == NULL\n");
#endif
	return;
    }

    if ((buf->alloc == XML_BUFFER_ALLOC_IO) &&
        (buf->contentIO != NULL)) {
        xmlFree(buf->contentIO);
    } else if ((buf->content != NULL) &&
        (buf->alloc != XML_BUFFER_ALLOC_IMMUTABLE)) {
        xmlFree(buf->content);
    }
    xmlFree(buf);
}