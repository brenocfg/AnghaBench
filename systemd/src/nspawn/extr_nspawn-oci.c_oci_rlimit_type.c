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
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int*) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_variant_string (int /*<<< orphan*/ *) ; 
 int rlimit_from_string (char const*) ; 
 char* startswith (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int oci_rlimit_type(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        const char *z;
        int t, *type = userdata;

        assert_se(type);

        z = startswith(json_variant_string(v), "RLIMIT_");
        if (!z)
                return json_log(v, flags, SYNTHETIC_ERRNO(EINVAL),
                                "rlimit entry's name does not begin with 'RLIMIT_', refusing: %s",
                                json_variant_string(v));

        t = rlimit_from_string(z);
        if (t < 0)
                return json_log(v, flags, SYNTHETIC_ERRNO(EINVAL),
                                "rlimit name unknown: %s", json_variant_string(v));

        *type = t;
        return 0;
}