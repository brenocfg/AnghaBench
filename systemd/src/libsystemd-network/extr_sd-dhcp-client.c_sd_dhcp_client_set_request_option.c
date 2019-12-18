#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {size_t req_opts_size; int* req_opts; int /*<<< orphan*/  req_opts_allocated; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ sd_dhcp_client ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_STATE_INIT ; 
 int /*<<< orphan*/  DHCP_STATE_STOPPED ; 
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GREEDY_REALLOC (int*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SD_DHCP_OPTION_END 132 
#define  SD_DHCP_OPTION_MESSAGE_TYPE 131 
#define  SD_DHCP_OPTION_OVERLOAD 130 
#define  SD_DHCP_OPTION_PAD 129 
#define  SD_DHCP_OPTION_PARAMETER_REQUEST_LIST 128 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int) ; 

int sd_dhcp_client_set_request_option(sd_dhcp_client *client, uint8_t option) {
        size_t i;

        assert_return(client, -EINVAL);
        assert_return(IN_SET(client->state, DHCP_STATE_INIT, DHCP_STATE_STOPPED), -EBUSY);

        switch(option) {

        case SD_DHCP_OPTION_PAD:
        case SD_DHCP_OPTION_OVERLOAD:
        case SD_DHCP_OPTION_MESSAGE_TYPE:
        case SD_DHCP_OPTION_PARAMETER_REQUEST_LIST:
        case SD_DHCP_OPTION_END:
                return -EINVAL;

        default:
                break;
        }

        for (i = 0; i < client->req_opts_size; i++)
                if (client->req_opts[i] == option)
                        return -EEXIST;

        if (!GREEDY_REALLOC(client->req_opts, client->req_opts_allocated,
                            client->req_opts_size + 1))
                return -ENOMEM;

        client->req_opts[client->req_opts_size++] = option;

        return 0;
}