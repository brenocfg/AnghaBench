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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sd_netlink_message ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  NETLINK_TYPE_U32 ; 
 int /*<<< orphan*/  assert_return (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int message_attribute_has_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ) ; 
 int netlink_message_read_internal (int /*<<< orphan*/ *,unsigned short,void**,int*) ; 

int sd_netlink_message_read_u32(sd_netlink_message *m, unsigned short type, uint32_t *data) {
        void *attr_data;
        bool net_byteorder;
        int r;

        assert_return(m, -EINVAL);

        r = message_attribute_has_type(m, NULL, type, NETLINK_TYPE_U32);
        if (r < 0)
                return r;

        r = netlink_message_read_internal(m, type, &attr_data, &net_byteorder);
        if (r < 0)
                return r;
        else if ((size_t)r < sizeof(uint32_t))
                return -EIO;

        if (data) {
                if (net_byteorder)
                        *data = be32toh(*(uint32_t *) attr_data);
                else
                        *data = *(uint32_t *) attr_data;
        }

        return 0;
}