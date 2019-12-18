#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  sd_lldp_neighbor ;
typedef  int /*<<< orphan*/  sd_lldp ;
typedef  int /*<<< orphan*/  sd_event ;
typedef  int /*<<< orphan*/  frame ;

/* Variables and functions */
 int /*<<< orphan*/  SD_LLDP_OUI_802_1 ; 
 int /*<<< orphan*/  SD_LLDP_OUI_802_1_SUBTYPE_LINK_AGGREGATION ; 
 int /*<<< orphan*/  SD_LLDP_OUI_802_1_SUBTYPE_MANAGEMENT_VID ; 
 int /*<<< orphan*/  SD_LLDP_OUI_802_1_SUBTYPE_PORT_PROTOCOL_VLAN_ID ; 
 int /*<<< orphan*/  SD_LLDP_OUI_802_1_SUBTYPE_PORT_VLAN_ID ; 
 int /*<<< orphan*/  SD_LLDP_OUI_802_1_SUBTYPE_VLAN_NAME ; 
 int /*<<< orphan*/  SD_LLDP_OUI_802_3 ; 
 int /*<<< orphan*/  SD_LLDP_OUI_802_3_SUBTYPE_POWER_VIA_MDI ; 
 int /*<<< orphan*/  SD_LLDP_TYPE_CHASSIS_ID ; 
 int /*<<< orphan*/  SD_LLDP_TYPE_END ; 
 int /*<<< orphan*/  SD_LLDP_TYPE_PORT_ID ; 
 int /*<<< orphan*/  SD_LLDP_TYPE_TTL ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lldp_handler ; 
 int lldp_handler_calls ; 
 int /*<<< orphan*/  sd_event_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_lldp_get_neighbors (int /*<<< orphan*/ *,int /*<<< orphan*/ ***) ; 
 scalar_t__ sd_lldp_neighbor_tlv_is_oui (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_lldp_neighbor_tlv_is_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_lldp_neighbor_tlv_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_lldp_neighbor_tlv_rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_lldp_neighbor_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ start_lldp (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stop_lldp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * test_fd ; 
 int write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void test_receive_oui_packet(sd_event *e) {
        sd_lldp *lldp;
        sd_lldp_neighbor **neighbors;
        uint8_t frame[] = {
                /* Ethernet header */
                0x01, 0x80, 0xc2, 0x00, 0x00, 0x03,     /* Destination MAC */
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06,     /* Source MAC */
                0x88, 0xcc,                             /* Ethertype */
                /* LLDP mandatory TLVs */
                0x02, 0x07, 0x04, 0x00, 0x01, 0x02,     /* Chassis: MAC, 00:01:02:03:04:05 */
                0x03, 0x04, 0x05,
                0x04, 0x04, 0x05, 0x31, 0x2f, 0x33,     /* Port TLV: interface name, "1/3" */
                0x06, 0x02, 0x00, 0x78,                 /* TTL: 120 seconds */
                /* LLDP optional TLVs */
                0xfe, 0x06, 0x00, 0x80, 0xc2, 0x01,     /* Port VLAN ID: 0x1234 */
                0x12, 0x34,
                0xfe, 0x07, 0x00, 0x80, 0xc2, 0x02,     /* Port and protocol: flag 1, PPVID 0x7788 */
                0x01, 0x77, 0x88,
                0xfe, 0x0d, 0x00, 0x80, 0xc2, 0x03,     /* VLAN Name: ID 0x1234, name "Vlan51" */
                0x12, 0x34, 0x06, 0x56, 0x6c, 0x61,
                0x6e, 0x35, 0x31,
                0xfe, 0x06, 0x00, 0x80, 0xc2, 0x06,     /* Management VID: 0x0102 */
                0x01, 0x02,
                0xfe, 0x09, 0x00, 0x80, 0xc2, 0x07,     /* Link aggregation: status 1, ID 0x00140012 */
                0x01, 0x00, 0x14, 0x00, 0x12,
                0xfe, 0x07, 0x00, 0x12, 0x0f, 0x02,     /* 802.3 Power via MDI: PSE, MDI enabled */
                0x07, 0x01, 0x00,
                0x00, 0x00                              /* End of LLDPDU */
        };

        lldp_handler_calls = 0;
        assert_se(start_lldp(&lldp, e, lldp_handler, NULL) == 0);

        assert_se(write(test_fd[1], frame, sizeof(frame)) == sizeof(frame));
        sd_event_run(e, 0);
        assert_se(lldp_handler_calls == 1);
        assert_se(sd_lldp_get_neighbors(lldp, &neighbors) == 1);

        assert_se(sd_lldp_neighbor_tlv_rewind(neighbors[0]) >= 0);
        assert_se(sd_lldp_neighbor_tlv_is_type(neighbors[0], SD_LLDP_TYPE_CHASSIS_ID) > 0);
        assert_se(sd_lldp_neighbor_tlv_next(neighbors[0]) > 0);
        assert_se(sd_lldp_neighbor_tlv_is_type(neighbors[0], SD_LLDP_TYPE_PORT_ID) > 0);
        assert_se(sd_lldp_neighbor_tlv_next(neighbors[0]) > 0);
        assert_se(sd_lldp_neighbor_tlv_is_type(neighbors[0], SD_LLDP_TYPE_TTL) > 0);
        assert_se(sd_lldp_neighbor_tlv_next(neighbors[0]) > 0);
        assert_se(sd_lldp_neighbor_tlv_is_oui(neighbors[0], SD_LLDP_OUI_802_1, SD_LLDP_OUI_802_1_SUBTYPE_PORT_VLAN_ID) > 0);
        assert_se(sd_lldp_neighbor_tlv_next(neighbors[0]) > 0);
        assert_se(sd_lldp_neighbor_tlv_is_oui(neighbors[0], SD_LLDP_OUI_802_1, SD_LLDP_OUI_802_1_SUBTYPE_PORT_PROTOCOL_VLAN_ID) > 0);
        assert_se(sd_lldp_neighbor_tlv_next(neighbors[0]) > 0);
        assert_se(sd_lldp_neighbor_tlv_is_oui(neighbors[0], SD_LLDP_OUI_802_1, SD_LLDP_OUI_802_1_SUBTYPE_VLAN_NAME) > 0);
        assert_se(sd_lldp_neighbor_tlv_next(neighbors[0]) > 0);
        assert_se(sd_lldp_neighbor_tlv_is_oui(neighbors[0], SD_LLDP_OUI_802_1, SD_LLDP_OUI_802_1_SUBTYPE_MANAGEMENT_VID) > 0);
        assert_se(sd_lldp_neighbor_tlv_next(neighbors[0]) > 0);
        assert_se(sd_lldp_neighbor_tlv_is_oui(neighbors[0], SD_LLDP_OUI_802_1, SD_LLDP_OUI_802_1_SUBTYPE_LINK_AGGREGATION) > 0);
        assert_se(sd_lldp_neighbor_tlv_next(neighbors[0]) > 0);
        assert_se(sd_lldp_neighbor_tlv_is_oui(neighbors[0], SD_LLDP_OUI_802_3, SD_LLDP_OUI_802_3_SUBTYPE_POWER_VIA_MDI) > 0);
        assert_se(sd_lldp_neighbor_tlv_next(neighbors[0]) > 0);
        assert_se(sd_lldp_neighbor_tlv_is_type(neighbors[0], SD_LLDP_TYPE_END) > 0);
        assert_se(sd_lldp_neighbor_tlv_next(neighbors[0]) == 0);

        sd_lldp_neighbor_unref(neighbors[0]);
        free(neighbors);

        assert_se(stop_lldp(lldp) == 0);
}