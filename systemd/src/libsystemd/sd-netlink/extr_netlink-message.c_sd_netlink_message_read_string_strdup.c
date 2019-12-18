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
 int ENOMEM ; 
 int /*<<< orphan*/  NETLINK_TYPE_STRING ; 
 int /*<<< orphan*/  assert_return (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int message_attribute_has_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ) ; 
 int netlink_message_read_internal (int /*<<< orphan*/ *,unsigned short,void**,int /*<<< orphan*/ *) ; 
 char* strndup (void*,int) ; 

int sd_netlink_message_read_string_strdup(sd_netlink_message *m, unsigned short type, char **data) {
        void *attr_data;
        char *str;
        int r;

        assert_return(m, -EINVAL);

        r = message_attribute_has_type(m, NULL, type, NETLINK_TYPE_STRING);
        if (r < 0)
                return r;

        r = netlink_message_read_internal(m, type, &attr_data, NULL);
        if (r < 0)
                return r;

        if (data) {
                str = strndup(attr_data, r);
                if (!str)
                        return -ENOMEM;

                *data = str;
        }

        return 0;
}