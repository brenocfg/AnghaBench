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
typedef  TYPE_1__* xmlParserInputBufferPtr ;
struct TYPE_4__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/ * readcallback; scalar_t__ error; } ;

/* Variables and functions */
 scalar_t__ XML_BUFFER_ALLOC_IMMUTABLE ; 
 scalar_t__ xmlBufGetAllocationScheme (int /*<<< orphan*/ ) ; 
 int xmlParserInputBufferGrow (TYPE_1__*,int) ; 

int
xmlParserInputBufferRead(xmlParserInputBufferPtr in, int len) {
    if ((in == NULL) || (in->error)) return(-1);
    if (in->readcallback != NULL)
	return(xmlParserInputBufferGrow(in, len));
    else if (xmlBufGetAllocationScheme(in->buffer) == XML_BUFFER_ALLOC_IMMUTABLE)
	return(0);
    else
        return(-1);
}