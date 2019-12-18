#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ xmlBufferAllocationScheme ;

/* Variables and functions */
 scalar_t__ XML_BUFFER_ALLOC_DOUBLEIT ; 
 scalar_t__ XML_BUFFER_ALLOC_EXACT ; 
 scalar_t__ XML_BUFFER_ALLOC_HYBRID ; 
 scalar_t__ xmlBufferAllocScheme ; 

void
xmlSetBufferAllocationScheme(xmlBufferAllocationScheme scheme) {
    if ((scheme == XML_BUFFER_ALLOC_EXACT) ||
        (scheme == XML_BUFFER_ALLOC_DOUBLEIT) ||
        (scheme == XML_BUFFER_ALLOC_HYBRID))
	xmlBufferAllocScheme = scheme;
}