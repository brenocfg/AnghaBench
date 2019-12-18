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
typedef  int /*<<< orphan*/  sd_bus_message ;

/* Variables and functions */
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int reply_dump(sd_bus_message *message, char *dump) {
        return sd_bus_reply_method_return(message, "s", dump);
}