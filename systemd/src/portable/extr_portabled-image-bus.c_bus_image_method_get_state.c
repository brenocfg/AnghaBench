#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  PortableState ;
typedef  TYPE_1__ Image ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int portable_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portable_state_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (TYPE_1__*) ; 
 int sd_bus_reply_method_return (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bus_image_method_get_state(
                sd_bus_message *message,
                void *userdata,
                sd_bus_error *error) {

        Image *image = userdata;
        PortableState state;
        int r;

        assert(message);
        assert(image);

        r = portable_get_state(
                        sd_bus_message_get_bus(message),
                        image->path,
                        0,
                        &state,
                        error);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, "s", portable_state_to_string(state));
}