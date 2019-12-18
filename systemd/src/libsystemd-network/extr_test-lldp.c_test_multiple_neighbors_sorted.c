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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  sd_lldp_neighbor ;
typedef  int /*<<< orphan*/  sd_lldp ;
typedef  int /*<<< orphan*/  sd_event ;
typedef  int /*<<< orphan*/  frame6 ;
typedef  int /*<<< orphan*/  frame5 ;
typedef  int /*<<< orphan*/  frame4 ;
typedef  int /*<<< orphan*/  frame3 ;
typedef  int /*<<< orphan*/  frame2 ;
typedef  int /*<<< orphan*/  frame1 ;

/* Variables and functions */
 int SD_LLDP_CHASSIS_SUBTYPE_CHASSIS_COMPONENT ; 
 int SD_LLDP_PORT_SUBTYPE_PORT_COMPONENT ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lldp_handler ; 
 int lldp_handler_calls ; 
 scalar_t__ memcmp (void const*,char const*,size_t) ; 
 int /*<<< orphan*/  sd_event_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_lldp_get_neighbors (int /*<<< orphan*/ *,int /*<<< orphan*/ ***) ; 
 scalar_t__ sd_lldp_neighbor_get_chassis_id (int /*<<< orphan*/ *,int*,void const**,size_t*) ; 
 scalar_t__ sd_lldp_neighbor_get_port_id (int /*<<< orphan*/ *,int*,void const**,size_t*) ; 
 scalar_t__ sd_lldp_neighbor_get_ttl (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  sd_lldp_neighbor_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ start_lldp (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stop_lldp (int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/ * test_fd ; 
 int write (int /*<<< orphan*/ ,int const*,int) ; 

__attribute__((used)) static void test_multiple_neighbors_sorted(sd_event *e) {

        static const uint8_t frame1[] = {
                /* Ethernet header */
                0x01, 0x80, 0xc2, 0x00, 0x00, 0x03,     /* Destination MAC */
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06,     /* Source MAC */
                0x88, 0xcc,                             /* Ethertype */
                /* LLDP mandatory TLVs */
                0x02, 0x04, 0x01, '1', '/', '2',        /* Chassis component: "1/2" */
                0x04, 0x04, 0x02, '2', '/', '3',        /* Port component: "2/3" */
                0x06, 0x02, 0x00, 0x78,                 /* TTL: 120 seconds */
                0x00, 0x00                              /* End Of LLDPDU */
        };
        static const uint8_t frame2[] = {
                /* Ethernet header */
                0x01, 0x80, 0xc2, 0x00, 0x00, 0x03,     /* Destination MAC */
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06,     /* Source MAC */
                0x88, 0xcc,                             /* Ethertype */
                /* LLDP mandatory TLVs */
                0x02, 0x04, 0x01, '2', '/', '1',        /* Chassis component: "2/1" */
                0x04, 0x04, 0x02, '1', '/', '3',        /* Port component: "1/3" */
                0x06, 0x02, 0x00, 0x78,                 /* TTL: 120 seconds */
                0x00, 0x00                              /* End Of LLDPDU */
        };
        static const uint8_t frame3[] = {
                /* Ethernet header */
                0x01, 0x80, 0xc2, 0x00, 0x00, 0x03,     /* Destination MAC */
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06,     /* Source MAC */
                0x88, 0xcc,                             /* Ethertype */
                /* LLDP mandatory TLVs */
                0x02, 0x05, 0x01, '2', '/', '1', '0',   /* Chassis component: "2/10" */
                0x04, 0x04, 0x02, '1', '/', '0',        /* Port component: "1/0" */
                0x06, 0x02, 0x00, 0x78,                 /* TTL: 120 seconds */
                0x00, 0x00                              /* End Of LLDPDU */
        };
        static const uint8_t frame4[] = {
                /* Ethernet header */
                0x01, 0x80, 0xc2, 0x00, 0x00, 0x03,     /* Destination MAC */
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06,     /* Source MAC */
                0x88, 0xcc,                             /* Ethertype */
                /* LLDP mandatory TLVs */
                0x02, 0x05, 0x01, '2', '/', '1', '9',   /* Chassis component: "2/19" */
                0x04, 0x04, 0x02, '1', '/', '0',        /* Port component: "1/0" */
                0x06, 0x02, 0x00, 0x78,                 /* TTL: 120 seconds */
                0x00, 0x00                              /* End Of LLDPDU */
        };
        static const uint8_t frame5[] = {
                /* Ethernet header */
                0x01, 0x80, 0xc2, 0x00, 0x00, 0x03,     /* Destination MAC */
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06,     /* Source MAC */
                0x88, 0xcc,                             /* Ethertype */
                /* LLDP mandatory TLVs */
                0x02, 0x04, 0x01, '1', '/', '2',        /* Chassis component: "1/2" */
                0x04, 0x05, 0x02, '2', '/', '1', '0',   /* Port component: "2/10" */
                0x06, 0x02, 0x00, 0x78,                 /* TTL: 120 seconds */
                0x00, 0x00                              /* End Of LLDPDU */
        };
        static const uint8_t frame6[] = {
                /* Ethernet header */
                0x01, 0x80, 0xc2, 0x00, 0x00, 0x03,     /* Destination MAC */
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06,     /* Source MAC */
                0x88, 0xcc,                             /* Ethertype */
                /* LLDP mandatory TLVs */
                0x02, 0x04, 0x01, '1', '/', '2',        /* Chassis component: "1/2" */
                0x04, 0x05, 0x02, '2', '/', '3', '9',   /* Port component: "2/10" */
                0x06, 0x02, 0x00, 0x78,                 /* TTL: 120 seconds */
                0x00, 0x00                              /* End Of LLDPDU */
        };
        static const char* expected[] = {
                /* ordered pairs of Chassis+Port */
                "1/2", "2/10",
                "1/2", "2/3",
                "1/2", "2/39",
                "2/1", "1/3",
                "2/10", "1/0",
                "2/19", "1/0",
        };

        sd_lldp *lldp;
        sd_lldp_neighbor **neighbors;
        int i;
        uint8_t type;
        const void *data;
        size_t length, expected_length;
        uint16_t ttl;

        lldp_handler_calls = 0;
        assert_se(start_lldp(&lldp, e, lldp_handler, NULL) == 0);

        assert_se(write(test_fd[1], frame1, sizeof(frame1)) == sizeof(frame1));
        sd_event_run(e, 0);
        assert_se(write(test_fd[1], frame2, sizeof(frame2)) == sizeof(frame2));
        sd_event_run(e, 0);
        assert_se(write(test_fd[1], frame3, sizeof(frame3)) == sizeof(frame3));
        sd_event_run(e, 0);
        assert_se(write(test_fd[1], frame4, sizeof(frame4)) == sizeof(frame4));
        sd_event_run(e, 0);
        assert_se(write(test_fd[1], frame5, sizeof(frame5)) == sizeof(frame5));
        sd_event_run(e, 0);
        assert_se(write(test_fd[1], frame6, sizeof(frame6)) == sizeof(frame6));
        sd_event_run(e, 0);
        assert_se(lldp_handler_calls == 6);

        assert_se(sd_lldp_get_neighbors(lldp, &neighbors) == 6);

        for (i = 0; i < 6; i++) {
                assert_se(sd_lldp_neighbor_get_chassis_id(neighbors[i], &type, &data, &length) == 0);
                assert_se(type == SD_LLDP_CHASSIS_SUBTYPE_CHASSIS_COMPONENT);
                expected_length = strlen(expected[2 * i]);
                assert_se(length == expected_length);
                assert_se(memcmp(data, expected[2 * i], expected_length) == 0);

                assert_se(sd_lldp_neighbor_get_port_id(neighbors[i], &type, &data, &length) == 0);
                assert_se(type == SD_LLDP_PORT_SUBTYPE_PORT_COMPONENT);
                expected_length = strlen(expected[2 * i + 1]);
                assert_se(length == expected_length);
                assert_se(memcmp(data, expected[2 * i + 1], expected_length) == 0);

                assert_se(sd_lldp_neighbor_get_ttl(neighbors[i], &ttl) == 0);
                assert_se(ttl == 120);
        }

        for (i = 0; i < 6; i++)
                sd_lldp_neighbor_unref(neighbors[i]);
        free(neighbors);

        assert_se(stop_lldp(lldp) == 0);
}