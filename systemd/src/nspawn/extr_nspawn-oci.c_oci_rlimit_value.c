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
typedef  scalar_t__ uintmax_t ;
typedef  scalar_t__ rlim_t ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 scalar_t__ RLIM_INFINITY ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (scalar_t__*) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ json_variant_is_negative (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_variant_is_unsigned (int /*<<< orphan*/ *) ; 
 scalar_t__ json_variant_unsigned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oci_rlimit_value(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        rlim_t z, *value = userdata;

        assert(value);

        if (json_variant_is_negative(v))
                z = RLIM_INFINITY;
        else {
                if (!json_variant_is_unsigned(v))
                        return json_log(v, flags, SYNTHETIC_ERRNO(ERANGE),
                                        "rlimits limit not unsigned, refusing.");

                z = (rlim_t) json_variant_unsigned(v);

                if ((uintmax_t) z != json_variant_unsigned(v))
                        return json_log(v, flags, SYNTHETIC_ERRNO(EINVAL),
                                        "rlimits limit out of range, refusing.");
        }

        *value = z;
        return 0;
}