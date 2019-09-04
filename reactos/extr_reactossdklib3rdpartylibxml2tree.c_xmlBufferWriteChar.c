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
struct TYPE_4__ {scalar_t__ alloc; } ;

/* Variables and functions */
 scalar_t__ XML_BUFFER_ALLOC_IMMUTABLE ; 
 int /*<<< orphan*/  xmlBufferCCat (TYPE_1__*,char const*) ; 

void
xmlBufferWriteChar(xmlBufferPtr buf, const char *string) {
    if (buf == NULL)
        return;
    if (buf->alloc == XML_BUFFER_ALLOC_IMMUTABLE) return;
    xmlBufferCCat(buf, string);
}