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
typedef  int /*<<< orphan*/  PortableState ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int portable_get_state (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portable_state_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int method_get_image_state(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        const char *name_or_path;
        PortableState state;
        int r;

        assert(message);

        r = sd_bus_message_read(message, "s", &name_or_path);
        if (r < 0)
                return r;

        r = portable_get_state(
                        sd_bus_message_get_bus(message),
                        name_or_path,
                        0,
                        &state,
                        error);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, "s", portable_state_to_string(state));
}