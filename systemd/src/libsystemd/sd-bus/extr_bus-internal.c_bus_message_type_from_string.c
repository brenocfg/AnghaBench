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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SD_BUS_MESSAGE_METHOD_CALL ; 
 int /*<<< orphan*/  SD_BUS_MESSAGE_METHOD_ERROR ; 
 int /*<<< orphan*/  SD_BUS_MESSAGE_METHOD_RETURN ; 
 int /*<<< orphan*/  SD_BUS_MESSAGE_SIGNAL ; 
 scalar_t__ streq (char const*,char*) ; 

int bus_message_type_from_string(const char *s, uint8_t *u) {
        if (streq(s, "signal"))
                *u = SD_BUS_MESSAGE_SIGNAL;
        else if (streq(s, "method_call"))
                *u = SD_BUS_MESSAGE_METHOD_CALL;
        else if (streq(s, "error"))
                *u = SD_BUS_MESSAGE_METHOD_ERROR;
        else if (streq(s, "method_return"))
                *u = SD_BUS_MESSAGE_METHOD_RETURN;
        else
                return -EINVAL;

        return 0;
}