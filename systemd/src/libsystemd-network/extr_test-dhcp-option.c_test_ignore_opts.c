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

/* Variables and functions */
#define  SD_DHCP_OPTION_MESSAGE_TYPE 130 
#define  SD_DHCP_OPTION_OVERLOAD 129 
#define  SD_DHCP_OPTION_PAD 128 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void test_ignore_opts(uint8_t *descoption, int *descpos, int *desclen) {
        assert(*descpos >= 0);

        while (*descpos < *desclen) {
                switch(descoption[*descpos]) {
                case SD_DHCP_OPTION_PAD:
                        *descpos += 1;
                        break;

                case SD_DHCP_OPTION_MESSAGE_TYPE:
                case SD_DHCP_OPTION_OVERLOAD:
                        *descpos += 3;
                        break;

                default:
                        return;
                }
        }
}