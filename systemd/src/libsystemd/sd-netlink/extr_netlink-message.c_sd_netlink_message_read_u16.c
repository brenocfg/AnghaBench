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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  sd_netlink_message ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  NETLINK_TYPE_U16 ; 
 int /*<<< orphan*/  assert_return (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int message_attribute_has_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ) ; 
 int netlink_message_read_internal (int /*<<< orphan*/ *,unsigned short,void**,int*) ; 

int sd_netlink_message_read_u16(sd_netlink_message *m, unsigned short type, uint16_t *data) {
        void *attr_data;
        bool net_byteorder;
        int r;

        assert_return(m, -EINVAL);

        r = message_attribute_has_type(m, NULL, type, NETLINK_TYPE_U16);
        if (r < 0)
                return r;

        r = netlink_message_read_internal(m, type, &attr_data, &net_byteorder);
        if (r < 0)
                return r;
        else if ((size_t) r < sizeof(uint16_t))
                return -EIO;

        if (data) {
                if (net_byteorder)
                        *data = be16toh(*(uint16_t *) attr_data);
                else
                        *data = *(uint16_t *) attr_data;
        }

        return 0;
}