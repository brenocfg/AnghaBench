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
typedef  int /*<<< orphan*/  xmlDeregisterNodeFunc ;

/* Variables and functions */
 int __xmlRegisterCallbacks ; 
 int /*<<< orphan*/  xmlDeregisterNodeDefaultValueThrDef ; 
 int /*<<< orphan*/  xmlMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlThrDefMutex ; 

xmlDeregisterNodeFunc
xmlThrDefDeregisterNodeDefault(xmlDeregisterNodeFunc func)
{
    xmlDeregisterNodeFunc old;

    xmlMutexLock(xmlThrDefMutex);
    old = xmlDeregisterNodeDefaultValueThrDef;

    __xmlRegisterCallbacks = 1;
    xmlDeregisterNodeDefaultValueThrDef = func;
    xmlMutexUnlock(xmlThrDefMutex);

    return(old);
}