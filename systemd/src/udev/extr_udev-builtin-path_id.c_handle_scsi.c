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
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 int /*<<< orphan*/ * handle_scsi_ata (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * handle_scsi_default (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * handle_scsi_fibre_channel (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * handle_scsi_hyperv (int /*<<< orphan*/ *,char**,int) ; 
 int /*<<< orphan*/ * handle_scsi_iscsi (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * handle_scsi_sas (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  path_prepend (char**,char*,char const*) ; 
 scalar_t__ sd_device_get_devtype (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ sd_device_get_sysattr_value (int /*<<< orphan*/ *,char*,char const**) ; 
 scalar_t__ sd_device_get_syspath (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/ * skip_subsystem (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  streq (char const*,char*) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static sd_device *handle_scsi(sd_device *parent, char **path, bool *supported_parent) {
        const char *devtype, *id, *name;

        if (sd_device_get_devtype(parent, &devtype) < 0 ||
            !streq(devtype, "scsi_device"))
                return parent;

        /* firewire */
        if (sd_device_get_sysattr_value(parent, "ieee1394_id", &id) >= 0) {
                path_prepend(path, "ieee1394-0x%s", id);
                *supported_parent = true;
                return skip_subsystem(parent, "scsi");
        }

        /* scsi sysfs does not have a "subsystem" for the transport */
        if (sd_device_get_syspath(parent, &name) < 0)
                return NULL;

        if (strstr(name, "/rport-")) {
                *supported_parent = true;
                return handle_scsi_fibre_channel(parent, path);
        }

        if (strstr(name, "/end_device-")) {
                *supported_parent = true;
                return handle_scsi_sas(parent, path);
        }

        if (strstr(name, "/session")) {
                *supported_parent = true;
                return handle_scsi_iscsi(parent, path);
        }

        if (strstr(name, "/ata"))
                return handle_scsi_ata(parent, path);

        if (strstr(name, "/vmbus_"))
                return handle_scsi_hyperv(parent, path, 37);
        else if (strstr(name, "/VMBUS"))
                return handle_scsi_hyperv(parent, path, 38);

        return handle_scsi_default(parent, path);
}