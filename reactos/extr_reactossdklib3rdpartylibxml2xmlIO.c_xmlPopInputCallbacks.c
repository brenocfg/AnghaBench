#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * closecallback; int /*<<< orphan*/ * readcallback; int /*<<< orphan*/ * opencallback; int /*<<< orphan*/ * matchcallback; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlInputCallbackInitialized ; 
 size_t xmlInputCallbackNr ; 
 TYPE_1__* xmlInputCallbackTable ; 

int
xmlPopInputCallbacks(void)
{
    if (!xmlInputCallbackInitialized)
        return(-1);

    if (xmlInputCallbackNr <= 0)
        return(-1);

    xmlInputCallbackNr--;
    xmlInputCallbackTable[xmlInputCallbackNr].matchcallback = NULL;
    xmlInputCallbackTable[xmlInputCallbackNr].opencallback = NULL;
    xmlInputCallbackTable[xmlInputCallbackNr].readcallback = NULL;
    xmlInputCallbackTable[xmlInputCallbackNr].closecallback = NULL;

    return(xmlInputCallbackNr);
}