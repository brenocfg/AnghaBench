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

/* Variables and functions */
 int /*<<< orphan*/  xmlMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexUnlock (int /*<<< orphan*/ ) ; 
 int xmlPedanticParserDefaultValueThrDef ; 
 int /*<<< orphan*/  xmlThrDefMutex ; 

int xmlThrDefPedanticParserDefaultValue(int v) {
    int ret;
    xmlMutexLock(xmlThrDefMutex);
    ret = xmlPedanticParserDefaultValueThrDef;
    xmlPedanticParserDefaultValueThrDef = v;
    xmlMutexUnlock(xmlThrDefMutex);
    return ret;
}