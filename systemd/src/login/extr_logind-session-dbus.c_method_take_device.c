#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_16__ {int /*<<< orphan*/  devices; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_17__ {int /*<<< orphan*/  active; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ SessionDevice ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_DEVICE_IS_TAKEN ; 
 int /*<<< orphan*/  BUS_ERROR_NOT_IN_CONTROL ; 
 int /*<<< orphan*/  DEVICE_MAJOR_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEVICE_MINOR_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_2__* hashmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makedev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sd_bus_message_get_sender (TYPE_1__*) ; 
 int sd_bus_message_read (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_bus_reply_method_return (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  session_device_free (TYPE_2__*) ; 
 int session_device_new (TYPE_1__*,int /*<<< orphan*/ ,int,TYPE_2__**) ; 
 int session_device_save (TYPE_2__*) ; 
 int /*<<< orphan*/  session_is_controller (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_save (TYPE_1__*) ; 

__attribute__((used)) static int method_take_device(sd_bus_message *message, void *userdata, sd_bus_error *error) {
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
        if (sd)
                /* We don't allow retrieving a device multiple times.
                 * The related ReleaseDevice call is not ref-counted.
                 * The caller should use dup() if it requires more
                 * than one fd (it would be functionally
                 * equivalent). */
                return sd_bus_error_setf(error, BUS_ERROR_DEVICE_IS_TAKEN, "Device already taken");

        r = session_device_new(s, dev, true, &sd);
        if (r < 0)
                return r;

        r = session_device_save(sd);
        if (r < 0)
                goto error;

        r = sd_bus_reply_method_return(message, "hb", sd->fd, !sd->active);
        if (r < 0)
                goto error;

        session_save(s);
        return 1;

error:
        session_device_free(sd);
        return r;
}