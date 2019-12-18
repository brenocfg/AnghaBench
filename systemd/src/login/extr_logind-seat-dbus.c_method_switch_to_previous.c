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
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  Seat ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int seat_switch_to_previous (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_switch_to_previous(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Seat *s = userdata;
        int r;

        assert(message);
        assert(s);

        r = seat_switch_to_previous(s);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, NULL);
}