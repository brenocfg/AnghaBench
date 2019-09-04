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
typedef  int /*<<< orphan*/  xmlCharEncoding ;
typedef  scalar_t__ ptrdiff_t ;
struct TYPE_4__ {int /*<<< orphan*/  closecallback; int /*<<< orphan*/  readcallback; void* context; } ;

/* Variables and functions */
 TYPE_1__* xmlAllocParserInputBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFdClose ; 
 int /*<<< orphan*/  xmlFdRead ; 

xmlParserInputBufferPtr
xmlParserInputBufferCreateFd(int fd, xmlCharEncoding enc) {
    xmlParserInputBufferPtr ret;

    if (fd < 0) return(NULL);

    ret = xmlAllocParserInputBuffer(enc);
    if (ret != NULL) {
        ret->context = (void *) (ptrdiff_t) fd;
	ret->readcallback = xmlFdRead;
	ret->closecallback = xmlFdClose;
    }

    return(ret);
}