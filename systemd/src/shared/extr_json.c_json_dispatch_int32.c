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
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 scalar_t__ INT32_MAX ; 
 scalar_t__ INT32_MIN ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (scalar_t__*) ; 
 int json_log (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ json_variant_integer (scalar_t__*) ; 
 int /*<<< orphan*/  json_variant_is_integer (scalar_t__*) ; 
 int /*<<< orphan*/  strna (char const*) ; 

int json_dispatch_int32(const char *name, JsonVariant *variant, JsonDispatchFlags flags, void *userdata) {
        int32_t *i = userdata;

        assert(variant);
        assert(i);

        if (!json_variant_is_integer(variant))
                return json_log(variant, flags, SYNTHETIC_ERRNO(EINVAL), "JSON field '%s' is not an integer.", strna(name));

        if (json_variant_integer(variant) < INT32_MIN || json_variant_integer(variant) > INT32_MAX)
                return json_log(variant, flags, SYNTHETIC_ERRNO(ERANGE), "JSON field '%s' out of bounds.", strna(name));

        *i = (int32_t) json_variant_integer(variant);
        return 0;
}