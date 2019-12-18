#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct TYPE_8__ {int in_userns; int type; } ;
typedef  TYPE_1__ CustomMount ;

/* Variables and functions */
#define  CUSTOM_MOUNT_ARBITRARY 132 
#define  CUSTOM_MOUNT_BIND 131 
#define  CUSTOM_MOUNT_INACCESSIBLE 130 
#define  CUSTOM_MOUNT_OVERLAY 129 
#define  CUSTOM_MOUNT_TMPFS 128 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int mount_arbitrary (char const*,TYPE_1__*) ; 
 int mount_bind (char const*,TYPE_1__*) ; 
 int mount_inaccessible (char const*,TYPE_1__*) ; 
 int mount_overlay (char const*,TYPE_1__*) ; 
 int mount_tmpfs (char const*,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int mount_custom(
                const char *dest,
                CustomMount *mounts, size_t n,
                bool userns, uid_t uid_shift, uid_t uid_range,
                const char *selinux_apifs_context,
                bool in_userns) {

        size_t i;
        int r;

        assert(dest);

        for (i = 0; i < n; i++) {
                CustomMount *m = mounts + i;

                if (m->in_userns != in_userns)
                        continue;

                switch (m->type) {

                case CUSTOM_MOUNT_BIND:
                        r = mount_bind(dest, m);
                        break;

                case CUSTOM_MOUNT_TMPFS:
                        r = mount_tmpfs(dest, m, userns, uid_shift, uid_range, selinux_apifs_context);
                        break;

                case CUSTOM_MOUNT_OVERLAY:
                        r = mount_overlay(dest, m);
                        break;

                case CUSTOM_MOUNT_INACCESSIBLE:
                        r = mount_inaccessible(dest, m);
                        break;

                case CUSTOM_MOUNT_ARBITRARY:
                        r = mount_arbitrary(dest, m);
                        break;

                default:
                        assert_not_reached("Unknown custom mount type");
                }

                if (r < 0)
                        return r;
        }

        return 0;
}