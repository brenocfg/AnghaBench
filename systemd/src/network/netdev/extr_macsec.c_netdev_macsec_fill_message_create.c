#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_netlink_message ;
struct TYPE_3__ {scalar_t__ port; scalar_t__ encrypt; scalar_t__ encoding_an; } ;
typedef  int /*<<< orphan*/  NetDev ;
typedef  TYPE_1__ MACsec ;
typedef  int /*<<< orphan*/  Link ;

/* Variables and functions */
 int /*<<< orphan*/  IFLA_MACSEC_ENCODING_SA ; 
 int /*<<< orphan*/  IFLA_MACSEC_ENCRYPT ; 
 int /*<<< orphan*/  IFLA_MACSEC_PORT ; 
 TYPE_1__* MACSEC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int log_netdev_error_errno (int /*<<< orphan*/ *,int,char*) ; 
 int sd_netlink_message_append_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int sd_netlink_message_append_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int netdev_macsec_fill_message_create(NetDev *netdev, Link *link, sd_netlink_message *m) {
        MACsec *v;
        int r;

        assert(netdev);
        assert(m);

        v = MACSEC(netdev);

        if (v->port > 0) {
                r = sd_netlink_message_append_u16(m, IFLA_MACSEC_PORT, v->port);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_MACSEC_PORT attribute: %m");
        }

        if (v->encrypt >= 0) {
                r = sd_netlink_message_append_u8(m, IFLA_MACSEC_ENCRYPT, v->encrypt);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append IFLA_MACSEC_ENCRYPT attribute: %m");
        }

        r = sd_netlink_message_append_u8(m, IFLA_MACSEC_ENCODING_SA, v->encoding_an);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append IFLA_MACSEC_ENCODING_SA attribute: %m");

        return r;
}