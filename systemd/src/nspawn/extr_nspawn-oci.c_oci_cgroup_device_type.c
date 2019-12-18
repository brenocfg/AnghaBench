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
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IFBLK ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  assert_se (char const*) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 char* json_variant_string (int /*<<< orphan*/ *) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int oci_cgroup_device_type(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        mode_t *mode = userdata;
        const char *n;

        assert_se(n = json_variant_string(v));

        if (streq(n, "c"))
                *mode = S_IFCHR;
        else if (streq(n, "b"))
                *mode = S_IFBLK;
        else
                return json_log(v, flags, SYNTHETIC_ERRNO(EINVAL),
                                "Control group device type unknown: %s", n);

        return 0;
}