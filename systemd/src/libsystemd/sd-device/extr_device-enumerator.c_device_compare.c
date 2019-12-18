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
 int CMP (int,int) ; 
 int /*<<< orphan*/  STRLEN (char*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ sd_device_get_devpath (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ startswith (char const*,char*) ; 
 char* strchr (char const*,char) ; 
 int strcmp (char const*,char const*) ; 
 scalar_t__ strncmp (char const*,char const*,unsigned int) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static int device_compare(sd_device * const *_a, sd_device * const *_b) {
        sd_device *a = *(sd_device **)_a, *b = *(sd_device **)_b;
        const char *devpath_a, *devpath_b, *sound_a;
        bool delay_a, delay_b;
        int r;

        assert_se(sd_device_get_devpath(a, &devpath_a) >= 0);
        assert_se(sd_device_get_devpath(b, &devpath_b) >= 0);

        sound_a = strstr(devpath_a, "/sound/card");
        if (sound_a) {
                /* For sound cards the control device must be enumerated last to
                 * make sure it's the final device node that gets ACLs applied.
                 * Applications rely on this fact and use ACL changes on the
                 * control node as an indicator that the ACL change of the
                 * entire sound card completed. The kernel makes this guarantee
                 * when creating those devices, and hence we should too when
                 * enumerating them. */
                sound_a += STRLEN("/sound/card");
                sound_a = strchr(sound_a, '/');

                if (sound_a) {
                        unsigned prefix_len;

                        prefix_len = sound_a - devpath_a;

                        if (strncmp(devpath_a, devpath_b, prefix_len) == 0) {
                                const char *sound_b;

                                sound_b = devpath_b + prefix_len;

                                if (startswith(sound_a, "/controlC") &&
                                    !startswith(sound_b, "/contolC"))
                                        return 1;

                                if (!startswith(sound_a, "/controlC") &&
                                    startswith(sound_b, "/controlC"))
                                        return -1;
                        }
                }
        }

        /* md and dm devices are enumerated after all other devices */
        delay_a = strstr(devpath_a, "/block/md") || strstr(devpath_a, "/block/dm-");
        delay_b = strstr(devpath_b, "/block/md") || strstr(devpath_b, "/block/dm-");
        r = CMP(delay_a, delay_b);
        if (r != 0)
                return r;

        return strcmp(devpath_a, devpath_b);
}