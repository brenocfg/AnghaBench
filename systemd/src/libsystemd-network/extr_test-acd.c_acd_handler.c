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
typedef  int /*<<< orphan*/  sd_ipv4acd ;

/* Variables and functions */
#define  SD_IPV4ACD_EVENT_BIND 130 
#define  SD_IPV4ACD_EVENT_CONFLICT 129 
#define  SD_IPV4ACD_EVENT_STOP 128 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  log_info (char*) ; 

__attribute__((used)) static void acd_handler(sd_ipv4acd *acd, int event, void *userdata) {
        assert_se(acd);

        switch (event) {
        case SD_IPV4ACD_EVENT_BIND:
                log_info("bound");
                break;
        case SD_IPV4ACD_EVENT_CONFLICT:
                log_info("conflict");
                break;
        case SD_IPV4ACD_EVENT_STOP:
                log_error("the client was stopped");
                break;
        default:
                assert_not_reached("invalid ACD event");
        }
}