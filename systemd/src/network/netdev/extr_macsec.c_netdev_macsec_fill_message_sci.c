#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  as_uint64; } ;
typedef  TYPE_1__ sd_netlink_message ;
typedef  TYPE_1__ NetDev ;
typedef  TYPE_1__ MACsecSCI ;

/* Variables and functions */
 int /*<<< orphan*/  MACSEC_ATTR_RXSC_CONFIG ; 
 int /*<<< orphan*/  MACSEC_RXSC_ATTR_SCI ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int log_netdev_error_errno (TYPE_1__*,int,char*) ; 
 int sd_netlink_message_append_u64 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_netlink_message_close_container (TYPE_1__*) ; 
 int sd_netlink_message_open_container (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netdev_macsec_fill_message_sci(NetDev *netdev, MACsecSCI *sci, sd_netlink_message *m) {
        int r;

        assert(netdev);
        assert(m);
        assert(sci);

        r = sd_netlink_message_open_container(m, MACSEC_ATTR_RXSC_CONFIG);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append MACSEC_ATTR_RXSC_CONFIG attribute: %m");

        r = sd_netlink_message_append_u64(m, MACSEC_RXSC_ATTR_SCI, sci->as_uint64);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append MACSEC_RXSC_ATTR_SCI attribute: %m");

        r = sd_netlink_message_close_container(m);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append MACSEC_ATTR_RXSC_CONFIG attribute: %m");

        return 0;
}