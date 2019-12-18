#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct latencyTimeSeries {int idx; scalar_t__ max; TYPE_2__* samples; } ;
typedef  scalar_t__ mstime_t ;
struct TYPE_4__ {scalar_t__ time; scalar_t__ latency; } ;
struct TYPE_3__ {int /*<<< orphan*/  latency_events; } ;

/* Variables and functions */
 int LATENCY_TS_LEN ; 
 int /*<<< orphan*/  dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct latencyTimeSeries*) ; 
 struct latencyTimeSeries* dictFetchValue (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ server ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 struct latencyTimeSeries* zmalloc (int) ; 
 int /*<<< orphan*/  zstrdup (char const*) ; 

void latencyAddSample(const char *event, mstime_t latency) {
    struct latencyTimeSeries *ts = dictFetchValue(server.latency_events,event);
    time_t now = time(NULL);
    int prev;

    /* Create the time series if it does not exist. */
    if (ts == NULL) {
        ts = zmalloc(sizeof(*ts));
        ts->idx = 0;
        ts->max = 0;
        memset(ts->samples,0,sizeof(ts->samples));
        dictAdd(server.latency_events,zstrdup(event),ts);
    }

    if (latency > ts->max) ts->max = latency;

    /* If the previous sample is in the same second, we update our old sample
     * if this latency is > of the old one, or just return. */
    prev = (ts->idx + LATENCY_TS_LEN - 1) % LATENCY_TS_LEN;
    if (ts->samples[prev].time == now) {
        if (latency > ts->samples[prev].latency)
            ts->samples[prev].latency = latency;
        return;
    }

    ts->samples[ts->idx].time = time(NULL);
    ts->samples[ts->idx].latency = latency;

    ts->idx++;
    if (ts->idx == LATENCY_TS_LEN) ts->idx = 0;
}