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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  assert (scalar_t__*) ; 
 int json_log (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_variant_is_unsigned (scalar_t__*) ; 
 scalar_t__ json_variant_unsigned (scalar_t__*) ; 
 int /*<<< orphan*/  strna (char const*) ; 

int json_dispatch_uint32(const char *name, JsonVariant *variant, JsonDispatchFlags flags, void *userdata) {
        uint32_t *u = userdata;

        assert(variant);
        assert(u);

        if (!json_variant_is_unsigned(variant))
                return json_log(variant, flags, SYNTHETIC_ERRNO(EINVAL), "JSON field '%s' is not an unsigned integer.", strna(name));

        if (json_variant_unsigned(variant) > UINT32_MAX)
                return json_log(variant, flags, SYNTHETIC_ERRNO(ERANGE), "JSON field '%s' out of bounds.", strna(name));

        *u = (uint32_t) json_variant_unsigned(variant);
        return 0;
}