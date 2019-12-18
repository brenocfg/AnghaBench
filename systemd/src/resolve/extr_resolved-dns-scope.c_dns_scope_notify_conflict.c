#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  jitter ;
struct TYPE_11__ {scalar_t__ conflict_event_source; TYPE_1__* manager; int /*<<< orphan*/  key; int /*<<< orphan*/  conflict_queue; } ;
struct TYPE_10__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ DnsScope ;
typedef  TYPE_2__ DnsResourceRecord ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 scalar_t__ IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLMNR_JITTER_INTERVAL_USEC ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  clock_boottime_or_monotonic () ; 
 int /*<<< orphan*/  dns_resource_key_hash_ops ; 
 int /*<<< orphan*/  dns_resource_key_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_resource_record_ref (TYPE_2__*) ; 
 int log_debug_errno (int,char*) ; 
 int /*<<< orphan*/  log_oom () ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_conflict_dispatch ; 
 int ordered_hashmap_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ordered_hashmap_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  random_bytes (int /*<<< orphan*/ *,int) ; 
 int sd_event_add_time (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  sd_event_source_set_description (scalar_t__,char*) ; 

int dns_scope_notify_conflict(DnsScope *scope, DnsResourceRecord *rr) {
        usec_t jitter;
        int r;

        assert(scope);
        assert(rr);

        /* We don't send these queries immediately. Instead, we queue
         * them, and send them after some jitter delay. */
        r = ordered_hashmap_ensure_allocated(&scope->conflict_queue, &dns_resource_key_hash_ops);
        if (r < 0) {
                log_oom();
                return r;
        }

        /* We only place one RR per key in the conflict
         * messages, not all of them. That should be enough to
         * indicate where there might be a conflict */
        r = ordered_hashmap_put(scope->conflict_queue, rr->key, rr);
        if (IN_SET(r, 0, -EEXIST))
                return 0;
        if (r < 0)
                return log_debug_errno(r, "Failed to queue conflicting RR: %m");

        dns_resource_key_ref(rr->key);
        dns_resource_record_ref(rr);

        if (scope->conflict_event_source)
                return 0;

        random_bytes(&jitter, sizeof(jitter));
        jitter %= LLMNR_JITTER_INTERVAL_USEC;

        r = sd_event_add_time(scope->manager->event,
                              &scope->conflict_event_source,
                              clock_boottime_or_monotonic(),
                              now(clock_boottime_or_monotonic()) + jitter,
                              LLMNR_JITTER_INTERVAL_USEC,
                              on_conflict_dispatch, scope);
        if (r < 0)
                return log_debug_errno(r, "Failed to add conflict dispatch event: %m");

        (void) sd_event_source_set_description(scope->conflict_event_source, "scope-conflict");

        return 0;
}