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
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_variant_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_variant_is_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strna (char const*) ; 

int json_dispatch_integer(const char *name, JsonVariant *variant, JsonDispatchFlags flags, void *userdata) {
        intmax_t *i = userdata;

        assert(variant);
        assert(i);

        if (!json_variant_is_integer(variant))
                return json_log(variant, flags, SYNTHETIC_ERRNO(EINVAL), "JSON field '%s' is not an integer.", strna(name));

        *i = json_variant_integer(variant);
        return 0;
}