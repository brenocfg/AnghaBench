#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cpuset_mems; int /*<<< orphan*/  cpuset_cpus; void* ip_filters_egress; void* ip_filters_ingress; void* ip_address_deny; void* ip_address_allow; scalar_t__ device_allow; scalar_t__ blockio_device_bandwidths; scalar_t__ blockio_device_weights; scalar_t__ io_device_limits; scalar_t__ io_device_latencies; scalar_t__ io_device_weights; } ;
typedef  TYPE_1__ CGroupContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  cgroup_context_free_blockio_device_bandwidth (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  cgroup_context_free_blockio_device_weight (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  cgroup_context_free_device_allow (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  cgroup_context_free_io_device_latency (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  cgroup_context_free_io_device_limit (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  cgroup_context_free_io_device_weight (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_set_reset (int /*<<< orphan*/ *) ; 
 void* ip_address_access_free_all (void*) ; 
 void* strv_free (void*) ; 

void cgroup_context_done(CGroupContext *c) {
        assert(c);

        while (c->io_device_weights)
                cgroup_context_free_io_device_weight(c, c->io_device_weights);

        while (c->io_device_latencies)
                cgroup_context_free_io_device_latency(c, c->io_device_latencies);

        while (c->io_device_limits)
                cgroup_context_free_io_device_limit(c, c->io_device_limits);

        while (c->blockio_device_weights)
                cgroup_context_free_blockio_device_weight(c, c->blockio_device_weights);

        while (c->blockio_device_bandwidths)
                cgroup_context_free_blockio_device_bandwidth(c, c->blockio_device_bandwidths);

        while (c->device_allow)
                cgroup_context_free_device_allow(c, c->device_allow);

        c->ip_address_allow = ip_address_access_free_all(c->ip_address_allow);
        c->ip_address_deny = ip_address_access_free_all(c->ip_address_deny);

        c->ip_filters_ingress = strv_free(c->ip_filters_ingress);
        c->ip_filters_egress = strv_free(c->ip_filters_egress);

        cpu_set_reset(&c->cpuset_cpus);
        cpu_set_reset(&c->cpuset_mems);
}