#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ association_number; scalar_t__ packet_number; scalar_t__ key_len; scalar_t__ activate; int /*<<< orphan*/  key; int /*<<< orphan*/  key_id; } ;
typedef  TYPE_1__ sd_netlink_message ;
typedef  TYPE_1__ SecurityAssociation ;
typedef  TYPE_1__ NetDev ;

/* Variables and functions */
 int /*<<< orphan*/  MACSEC_ATTR_SA_CONFIG ; 
 scalar_t__ MACSEC_KEYID_LEN ; 
 int /*<<< orphan*/  MACSEC_SA_ATTR_ACTIVE ; 
 int /*<<< orphan*/  MACSEC_SA_ATTR_AN ; 
 int /*<<< orphan*/  MACSEC_SA_ATTR_KEY ; 
 int /*<<< orphan*/  MACSEC_SA_ATTR_KEYID ; 
 int /*<<< orphan*/  MACSEC_SA_ATTR_PN ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int log_netdev_error_errno (TYPE_1__*,int,char*) ; 
 int sd_netlink_message_append_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int sd_netlink_message_append_u32 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int sd_netlink_message_append_u8 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int sd_netlink_message_close_container (TYPE_1__*) ; 
 int sd_netlink_message_open_container (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netdev_macsec_fill_message_sa(NetDev *netdev, SecurityAssociation *a, sd_netlink_message *m) {
        int r;

        assert(netdev);
        assert(a);
        assert(m);

        r = sd_netlink_message_open_container(m, MACSEC_ATTR_SA_CONFIG);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append MACSEC_ATTR_SA_CONFIG attribute: %m");

        r = sd_netlink_message_append_u8(m, MACSEC_SA_ATTR_AN, a->association_number);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append MACSEC_SA_ATTR_AN attribute: %m");

        if (a->packet_number > 0) {
                r = sd_netlink_message_append_u32(m, MACSEC_SA_ATTR_PN, a->packet_number);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append MACSEC_SA_ATTR_PN attribute: %m");
        }

        if (a->key_len > 0) {
                r = sd_netlink_message_append_data(m, MACSEC_SA_ATTR_KEYID, a->key_id, MACSEC_KEYID_LEN);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append MACSEC_SA_ATTR_KEYID attribute: %m");

                r = sd_netlink_message_append_data(m, MACSEC_SA_ATTR_KEY, a->key, a->key_len);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append MACSEC_SA_ATTR_KEY attribute: %m");
        }

        if (a->activate >= 0) {
                r = sd_netlink_message_append_u8(m, MACSEC_SA_ATTR_ACTIVE, a->activate);
                if (r < 0)
                        return log_netdev_error_errno(netdev, r, "Could not append MACSEC_SA_ATTR_ACTIVE attribute: %m");
        }

        r = sd_netlink_message_close_container(m);
        if (r < 0)
                return log_netdev_error_errno(netdev, r, "Could not append MACSEC_ATTR_SA_CONFIG attribute: %m");

        return 0;
}