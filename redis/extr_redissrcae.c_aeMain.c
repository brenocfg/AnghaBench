#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* beforesleep ) (TYPE_1__*) ;scalar_t__ stop; } ;
typedef  TYPE_1__ aeEventLoop ;

/* Variables and functions */
 int AE_ALL_EVENTS ; 
 int AE_CALL_AFTER_SLEEP ; 
 int /*<<< orphan*/  aeProcessEvents (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void aeMain(aeEventLoop *eventLoop) {
    eventLoop->stop = 0;
    while (!eventLoop->stop) {
        if (eventLoop->beforesleep != NULL)
            eventLoop->beforesleep(eventLoop);
        aeProcessEvents(eventLoop, AE_ALL_EVENTS|AE_CALL_AFTER_SLEEP);
    }
}