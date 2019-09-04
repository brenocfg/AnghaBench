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
typedef  int /*<<< orphan*/  xmlBufferAllocationScheme ;

/* Variables and functions */
 int /*<<< orphan*/  xmlBufferAllocSchemeThrDef ; 
 int /*<<< orphan*/  xmlMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlThrDefMutex ; 

xmlBufferAllocationScheme xmlThrDefBufferAllocScheme(xmlBufferAllocationScheme v) {
    xmlBufferAllocationScheme ret;
    xmlMutexLock(xmlThrDefMutex);
    ret = xmlBufferAllocSchemeThrDef;
    xmlBufferAllocSchemeThrDef = v;
    xmlMutexUnlock(xmlThrDefMutex);
    return ret;
}