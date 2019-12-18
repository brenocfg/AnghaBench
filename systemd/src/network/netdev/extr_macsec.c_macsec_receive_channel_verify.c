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
struct TYPE_10__ {int /*<<< orphan*/  line; int /*<<< orphan*/  filename; } ;
struct TYPE_8__ {scalar_t__ port; int /*<<< orphan*/  as_uint64; int /*<<< orphan*/  mac; } ;
struct TYPE_9__ {TYPE_3__* section; TYPE_1__ sci; int /*<<< orphan*/  receive_channels; struct TYPE_9__* macsec; } ;
typedef  TYPE_2__ ReceiveChannel ;
typedef  int /*<<< orphan*/  NetDev ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/ * NETDEV (TYPE_2__*) ; 
 int SYNTHETIC_ERRNO (int) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 scalar_t__ ether_addr_is_null (int /*<<< orphan*/ *) ; 
 int log_netdev_error_errno (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int log_oom () ; 
 int ordered_hashmap_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ordered_hashmap_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ section_is_invalid (TYPE_3__*) ; 
 int /*<<< orphan*/  uint64_hash_ops ; 

__attribute__((used)) static int macsec_receive_channel_verify(ReceiveChannel *c) {
        NetDev *netdev;
        int r;

        assert(c);
        assert(c->macsec);

        netdev = NETDEV(c->macsec);

        if (section_is_invalid(c->section))
                return -EINVAL;

        if (ether_addr_is_null(&c->sci.mac))
                return log_netdev_error_errno(netdev, SYNTHETIC_ERRNO(EINVAL),
                                              "%s: MACsec receive channel without MAC address configured. "
                                              "Ignoring [MACsecReceiveChannel] section from line %u",
                                              c->section->filename, c->section->line);

        if (c->sci.port == 0)
                return log_netdev_error_errno(netdev, SYNTHETIC_ERRNO(EINVAL),
                                              "%s: MACsec receive channel without port configured. "
                                              "Ignoring [MACsecReceiveChannel] section from line %u",
                                              c->section->filename, c->section->line);

        r = ordered_hashmap_ensure_allocated(&c->macsec->receive_channels, &uint64_hash_ops);
        if (r < 0)
                return log_oom();

        r = ordered_hashmap_put(c->macsec->receive_channels, &c->sci.as_uint64, c);
        if (r == -EEXIST)
                return log_netdev_error_errno(netdev, r,
                                              "%s: Multiple [MACsecReceiveChannel] sections have same SCI, "
                                              "Ignoring [MACsecReceiveChannel] section from line %u",
                                              c->section->filename, c->section->line);
        if (r < 0)
                return log_netdev_error_errno(netdev, r,
                                              "%s: Failed to store [MACsecReceiveChannel] section at hashmap, "
                                              "Ignoring [MACsecReceiveChannel] section from line %u",
                                              c->section->filename, c->section->line);
        return 0;
}