#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  devices; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  int /*<<< orphan*/  SessionDevice ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_DEVICE_NOT_TAKEN ; 
 int /*<<< orphan*/  BUS_ERROR_NOT_IN_CONTROL ; 
 int /*<<< orphan*/  DEVICE_MAJOR_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEVICE_MINOR_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/ * hashmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makedev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sd_bus_message_get_sender (TYPE_1__*) ; 
 int sd_bus_message_read (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_bus_reply_method_return (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_device_complete_pause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_is_controller (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int method_pause_device_complete(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Session *s = userdata;
        uint32_t major, minor;
        SessionDevice *sd;
        dev_t dev;
        int r;

        assert(message);
        assert(s);

        r = sd_bus_message_read(message, "uu", &major, &minor);
        if (r < 0)
                return r;

        if (!DEVICE_MAJOR_VALID(major) || !DEVICE_MINOR_VALID(minor))
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Device major/minor is not valid.");

        if (!session_is_controller(s, sd_bus_message_get_sender(message)))
                return sd_bus_error_setf(error, BUS_ERROR_NOT_IN_CONTROL, "You are not in control of this session");

        dev = makedev(major, minor);
        sd = hashmap_get(s->devices, &dev);
        if (!sd)
                return sd_bus_error_setf(error, BUS_ERROR_DEVICE_NOT_TAKEN, "Device not taken");

        session_device_complete_pause(sd);

        return sd_bus_reply_method_return(message, NULL);
}