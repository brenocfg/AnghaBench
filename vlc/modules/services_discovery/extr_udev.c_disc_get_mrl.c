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
struct udev_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ atoi (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* udev_device_get_devnode (struct udev_device*) ; 
 char* udev_device_get_property_value (struct udev_device*,char*) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int vlc_open (char const*,int /*<<< orphan*/ ) ; 
 char* vlc_path2uri (char const*,char const*) ; 

__attribute__((used)) static char *disc_get_mrl (struct udev_device *dev)
{
    const char *node = udev_device_get_devnode (dev);
    const char *val;

    val = udev_device_get_property_value (dev, "ID_CDROM");
    if (val == NULL)
        return NULL; /* Ignore non-optical block devices */

    val = udev_device_get_property_value (dev, "ID_CDROM_MEDIA_STATE");
    if (val == NULL)
    {   /* Force probing of the disc in the drive if any. */
        int fd = vlc_open (node, O_RDONLY);
        if (fd != -1)
            vlc_close (fd);
        return NULL;
    }
    if (!strcmp (val, "blank"))
        return NULL; /* ignore empty drives and virgin recordable discs */

    const char *scheme = NULL;
    val = udev_device_get_property_value (dev,
                                          "ID_CDROM_MEDIA_TRACK_COUNT_AUDIO");
    if (val && atoi (val))
        scheme = "cdda"; /* Audio CD rather than file system */
    val = udev_device_get_property_value (dev, "ID_CDROM_MEDIA_DVD");
    if (val && atoi (val))
        scheme = "dvd";

    val = udev_device_get_property_value (dev, "ID_CDROM_MEDIA_BD");
    if (val && atoi (val))
        scheme = "bluray";
#ifdef LOL
    val = udev_device_get_property_value (dev, "ID_CDROM_MEDIA_HDDVD");
    if (val && atoi (val))
        scheme = "hddvd";
#endif

    /* We didn't get any property that could tell we have optical disc
       that we can play */
    if (scheme == NULL)
        return NULL;

    return vlc_path2uri (node, scheme);
}