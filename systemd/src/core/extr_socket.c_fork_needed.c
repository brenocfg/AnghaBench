#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_9__ {TYPE_1__ sa; } ;
struct TYPE_10__ {scalar_t__ network_namespace_path; scalar_t__ private_network; TYPE_2__ sockaddr; } ;
typedef  TYPE_3__ SocketAddress ;
typedef  TYPE_3__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int BPF_FIREWALL_UNSUPPORTED ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_3__ const*) ; 
 int bpf_firewall_supported () ; 

__attribute__((used)) static int fork_needed(const SocketAddress *address, const ExecContext *context) {
        int r;

        assert(address);
        assert(context);

        /* Check if we need to do the cgroup or netns stuff. If not we can do things much simpler. */

        if (IN_SET(address->sockaddr.sa.sa_family, AF_INET, AF_INET6)) {
                r = bpf_firewall_supported();
                if (r < 0)
                        return r;
                if (r != BPF_FIREWALL_UNSUPPORTED) /* If BPF firewalling isn't supported anyway — there's no point in this forking complexity */
                        return true;
        }

        return context->private_network || context->network_namespace_path;
}