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
typedef  int /*<<< orphan*/  sd_netlink_message ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  assert_return (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int netlink_message_read_internal (int /*<<< orphan*/ *,unsigned short,void**,int /*<<< orphan*/ *) ; 

int sd_netlink_message_read(sd_netlink_message *m, unsigned short type, size_t size, void *data) {
        void *attr_data;
        int r;

        assert_return(m, -EINVAL);

        r = netlink_message_read_internal(m, type, &attr_data, NULL);
        if (r < 0)
                return r;

        if ((size_t) r < size)
                return -EIO;

        if (data)
                memcpy(data, attr_data, size);

        return r;
}