#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ verified_feature_level; int /*<<< orphan*/  verified_usec; TYPE_1__* manager; } ;
struct TYPE_6__ {int /*<<< orphan*/  event; } ;
typedef  scalar_t__ DnsServerFeatureLevel ;
typedef  TYPE_2__ DnsServer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  clock_boottime_or_monotonic () ; 
 int /*<<< orphan*/  dns_server_feature_level_to_string (scalar_t__) ; 
 int /*<<< orphan*/  dns_server_string (TYPE_2__*) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_event_now (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dns_server_verified(DnsServer *s, DnsServerFeatureLevel level) {
        assert(s);

        if (s->verified_feature_level > level)
                return;

        if (s->verified_feature_level != level) {
                log_debug("Verified we get a response at feature level %s from DNS server %s.",
                          dns_server_feature_level_to_string(level),
                          dns_server_string(s));
                s->verified_feature_level = level;
        }

        assert_se(sd_event_now(s->manager->event, clock_boottime_or_monotonic(), &s->verified_usec) >= 0);
}