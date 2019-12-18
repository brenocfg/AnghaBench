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
typedef  scalar_t__ xmlChar ;
typedef  TYPE_1__* xmlBufferPtr ;
typedef  int /*<<< orphan*/  xmlBuffer ;
struct TYPE_4__ {int size; int /*<<< orphan*/ * contentIO; scalar_t__* content; int /*<<< orphan*/  alloc; scalar_t__ use; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlBufferAllocScheme ; 
 int xmlDefaultBufferSize ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 scalar_t__ xmlMalloc (int) ; 
 scalar_t__ xmlMallocAtomic (int) ; 
 int /*<<< orphan*/  xmlTreeErrMemory (char*) ; 

xmlBufferPtr
xmlBufferCreate(void) {
    xmlBufferPtr ret;

    ret = (xmlBufferPtr) xmlMalloc(sizeof(xmlBuffer));
    if (ret == NULL) {
	xmlTreeErrMemory("creating buffer");
        return(NULL);
    }
    ret->use = 0;
    ret->size = xmlDefaultBufferSize;
    ret->alloc = xmlBufferAllocScheme;
    ret->content = (xmlChar *) xmlMallocAtomic(ret->size * sizeof(xmlChar));
    if (ret->content == NULL) {
	xmlTreeErrMemory("creating buffer");
	xmlFree(ret);
        return(NULL);
    }
    ret->content[0] = 0;
    ret->contentIO = NULL;
    return(ret);
}