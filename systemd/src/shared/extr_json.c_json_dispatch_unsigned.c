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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_variant_is_unsigned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_variant_unsigned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strna (char const*) ; 

int json_dispatch_unsigned(const char *name, JsonVariant *variant, JsonDispatchFlags flags, void *userdata) {
        uintmax_t *u = userdata;

        assert(variant);
        assert(u);

        if (!json_variant_is_unsigned(variant))
                return json_log(variant, flags, SYNTHETIC_ERRNO(EINVAL), "JSON field '%s' is not an unsigned integer.", strna(name));

        *u = json_variant_unsigned(variant);
        return 0;
}