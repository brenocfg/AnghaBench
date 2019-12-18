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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  assert (scalar_t__*) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ json_variant_is_negative (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_variant_is_unsigned (int /*<<< orphan*/ *) ; 
 scalar_t__ json_variant_unsigned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oci_cgroup_memory_limit(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        uint64_t *m = userdata;
        uintmax_t k;

        assert(m);

        if (json_variant_is_negative(v)) {
                *m = UINT64_MAX;
                return 0;
        }

        if (!json_variant_is_unsigned(v))
                return json_log(v, flags, SYNTHETIC_ERRNO(EINVAL),
                                "Memory limit is not an unsigned integer");

        k = json_variant_unsigned(v);
        if (k >= UINT64_MAX)
                return json_log(v, flags, SYNTHETIC_ERRNO(ERANGE),
                                "Memory limit too large: %ji", k);

        *m = (uint64_t) k;
        return 0;
}