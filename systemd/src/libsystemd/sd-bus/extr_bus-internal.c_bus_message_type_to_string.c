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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ SD_BUS_MESSAGE_METHOD_CALL ; 
 scalar_t__ SD_BUS_MESSAGE_METHOD_ERROR ; 
 scalar_t__ SD_BUS_MESSAGE_METHOD_RETURN ; 
 scalar_t__ SD_BUS_MESSAGE_SIGNAL ; 

const char *bus_message_type_to_string(uint8_t u) {
        if (u == SD_BUS_MESSAGE_SIGNAL)
                return "signal";
        else if (u == SD_BUS_MESSAGE_METHOD_CALL)
                return "method_call";
        else if (u == SD_BUS_MESSAGE_METHOD_ERROR)
                return "error";
        else if (u == SD_BUS_MESSAGE_METHOD_RETURN)
                 return "method_return";
        else
                return NULL;
}