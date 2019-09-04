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
typedef  scalar_t__ xmlBufferAllocationScheme ;
struct TYPE_3__ {scalar_t__ alloc; } ;

/* Variables and functions */
 scalar_t__ XML_BUFFER_ALLOC_DOUBLEIT ; 
 scalar_t__ XML_BUFFER_ALLOC_EXACT ; 
 scalar_t__ XML_BUFFER_ALLOC_HYBRID ; 
 scalar_t__ XML_BUFFER_ALLOC_IMMUTABLE ; 
 scalar_t__ XML_BUFFER_ALLOC_IO ; 

void
xmlBufferSetAllocationScheme(xmlBufferPtr buf,
                             xmlBufferAllocationScheme scheme) {
    if (buf == NULL) {
#ifdef DEBUG_BUFFER
        xmlGenericError(xmlGenericErrorContext,
		"xmlBufferSetAllocationScheme: buf == NULL\n");
#endif
        return;
    }
    if ((buf->alloc == XML_BUFFER_ALLOC_IMMUTABLE) ||
        (buf->alloc == XML_BUFFER_ALLOC_IO)) return;
    if ((scheme == XML_BUFFER_ALLOC_DOUBLEIT) ||
        (scheme == XML_BUFFER_ALLOC_EXACT) ||
        (scheme == XML_BUFFER_ALLOC_HYBRID) ||
        (scheme == XML_BUFFER_ALLOC_IMMUTABLE))
	buf->alloc = scheme;
}