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
typedef  int mode_t ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ STR_IN_SET (char const*,char*,char*) ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int S_IFBLK ; 
 int S_IFCHR ; 
 int S_IFIFO ; 
 int S_IFMT ; 
 int /*<<< orphan*/  assert (int*) ; 
 int /*<<< orphan*/  assert_se (char const*) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 char* json_variant_string (int /*<<< orphan*/ *) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int oci_device_type(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        mode_t *mode = userdata;
        const char *t;

        assert(mode);
        assert_se(t = json_variant_string(v));

        if (STR_IN_SET(t, "c", "u"))
                *mode = (*mode & ~S_IFMT) | S_IFCHR;
        else if (streq(t, "b"))
                *mode = (*mode & ~S_IFMT) | S_IFBLK;
        else if (streq(t, "p"))
                *mode = (*mode & ~S_IFMT) | S_IFIFO;
        else
                return json_log(v, flags, SYNTHETIC_ERRNO(EINVAL),
                                "Unknown device type: %s", t);

        return 0;
}