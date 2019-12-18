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
typedef  int /*<<< orphan*/  sd_ipv4ll ;

/* Variables and functions */
#define  SD_IPV4LL_EVENT_BIND 129 
#define  SD_IPV4LL_EVENT_STOP 128 
 int /*<<< orphan*/  assert_se (int) ; 
 int basic_request_handler_bind ; 
 int basic_request_handler_stop ; 
 void* basic_request_handler_userdata ; 

__attribute__((used)) static void basic_request_handler(sd_ipv4ll *ll, int event, void *userdata) {
        assert_se(userdata == basic_request_handler_userdata);

        switch(event) {
                case SD_IPV4LL_EVENT_STOP:
                        basic_request_handler_stop = 1;
                        break;
                case SD_IPV4LL_EVENT_BIND:
                        basic_request_handler_bind = 1;
                        break;
                default:
                        assert_se(0);
                        break;
        }
}