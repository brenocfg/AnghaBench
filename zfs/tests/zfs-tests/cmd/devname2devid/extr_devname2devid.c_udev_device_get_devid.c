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
struct udev_list_entry {int dummy; } ;
struct udev_device {int dummy; } ;
typedef  int /*<<< orphan*/  devbyid ;

/* Variables and functions */
 char* DEV_BYID_PATH ; 
 int ENODATA ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  stpncpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 
 struct udev_list_entry* udev_device_get_devlinks_list_entry (struct udev_device*) ; 
 char* udev_device_get_property_value (struct udev_device*,char*) ; 
 char* udev_list_entry_get_name (struct udev_list_entry*) ; 
 struct udev_list_entry* udev_list_entry_get_next (struct udev_list_entry*) ; 

__attribute__((used)) static int
udev_device_get_devid(struct udev_device *dev, char *bufptr, size_t buflen)
{
	struct udev_list_entry *entry;
	const char *bus;
	char devbyid[MAXPATHLEN];

	/* The bus based by-id path is preferred */
	bus = udev_device_get_property_value(dev, "ID_BUS");

	if (bus == NULL) {
		const char *dm_uuid;

		/*
		 * For multipath nodes use the persistent uuid based identifier
		 *
		 * Example: 'dm-uuid-mpath-35000c5006304de3f'
		 */
		dm_uuid = udev_device_get_property_value(dev, "DM_UUID");
		if (dm_uuid != NULL) {
			(void) snprintf(bufptr, buflen, "dm-uuid-%s", dm_uuid);
			return (0);
		}
		return (ENODATA);
	}

	/*
	 * locate the bus specific by-id link
	 *
	 * Example: 'scsi-MG03SCA300_350000494a8cb3d67-part1'
	 */
	(void) snprintf(devbyid, sizeof (devbyid), "%s%s-", DEV_BYID_PATH, bus);
	entry = udev_device_get_devlinks_list_entry(dev);
	while (entry != NULL) {
		const char *name;

		name = udev_list_entry_get_name(entry);
		if (strncmp(name, devbyid, strlen(devbyid)) == 0) {
			name += strlen(DEV_BYID_PATH);
			(void) stpncpy(bufptr, name, buflen - 1);
			bufptr[buflen - 1] = '\0';
			return (0);
		}
		entry = udev_list_entry_get_next(entry);
	}

	return (ENODATA);
}