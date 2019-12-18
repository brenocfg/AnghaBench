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
typedef  int /*<<< orphan*/  xmlInputReadCallback ;
typedef  int /*<<< orphan*/  xmlInputOpenCallback ;
typedef  int /*<<< orphan*/  xmlInputMatchCallback ;
typedef  int /*<<< orphan*/  xmlInputCloseCallback ;
struct TYPE_2__ {int /*<<< orphan*/  closecallback; int /*<<< orphan*/  readcallback; int /*<<< orphan*/  opencallback; int /*<<< orphan*/  matchcallback; } ;

/* Variables and functions */
 size_t MAX_INPUT_CALLBACK ; 
 int xmlInputCallbackInitialized ; 
 size_t xmlInputCallbackNr ; 
 TYPE_1__* xmlInputCallbackTable ; 

int
xmlRegisterInputCallbacks(xmlInputMatchCallback matchFunc,
	xmlInputOpenCallback openFunc, xmlInputReadCallback readFunc,
	xmlInputCloseCallback closeFunc) {
    if (xmlInputCallbackNr >= MAX_INPUT_CALLBACK) {
	return(-1);
    }
    xmlInputCallbackTable[xmlInputCallbackNr].matchcallback = matchFunc;
    xmlInputCallbackTable[xmlInputCallbackNr].opencallback = openFunc;
    xmlInputCallbackTable[xmlInputCallbackNr].readcallback = readFunc;
    xmlInputCallbackTable[xmlInputCallbackNr].closecallback = closeFunc;
    xmlInputCallbackInitialized = 1;
    return(xmlInputCallbackNr++);
}