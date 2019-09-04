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
typedef  double uint64_t ;
struct TYPE_3__ {double requests; int start; } ;
typedef  TYPE_1__ thread ;
typedef  int /*<<< orphan*/  aeEventLoop ;
struct TYPE_4__ {int /*<<< orphan*/  requests; } ;

/* Variables and functions */
 int RECORD_INTERVAL_MS ; 
 int /*<<< orphan*/  aeStop (int /*<<< orphan*/ *) ; 
 TYPE_2__ statistics ; 
 int /*<<< orphan*/  stats_record (int /*<<< orphan*/ ,double) ; 
 scalar_t__ stop ; 
 int time_us () ; 

__attribute__((used)) static int record_rate(aeEventLoop *loop, long long id, void *data) {
    thread *thread = data;

    if (thread->requests > 0) {
        uint64_t elapsed_ms = (time_us() - thread->start) / 1000;
        uint64_t requests = (thread->requests / (double) elapsed_ms) * 1000;

        stats_record(statistics.requests, requests);

        thread->requests = 0;
        thread->start    = time_us();
    }

    if (stop) aeStop(loop);

    return RECORD_INTERVAL_MS;
}