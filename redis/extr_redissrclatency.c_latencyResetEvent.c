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
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_2__ {int /*<<< orphan*/  latency_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,char*) ; 
 char* dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 
 scalar_t__ strcasecmp (char*,char*) ; 

int latencyResetEvent(char *event_to_reset) {
    dictIterator *di;
    dictEntry *de;
    int resets = 0;

    di = dictGetSafeIterator(server.latency_events);
    while((de = dictNext(di)) != NULL) {
        char *event = dictGetKey(de);

        if (event_to_reset == NULL || strcasecmp(event,event_to_reset) == 0) {
            dictDelete(server.latency_events, event);
            resets++;
        }
    }
    dictReleaseIterator(di);
    return resets;
}