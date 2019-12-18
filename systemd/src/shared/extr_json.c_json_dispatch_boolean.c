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
typedef  int JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int*) ; 
 int json_log (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int json_variant_boolean (int*) ; 
 int /*<<< orphan*/  json_variant_is_boolean (int*) ; 
 int /*<<< orphan*/  strna (char const*) ; 

int json_dispatch_boolean(const char *name, JsonVariant *variant, JsonDispatchFlags flags, void *userdata) {
        bool *b = userdata;

        assert(variant);
        assert(b);

        if (!json_variant_is_boolean(variant))
                return json_log(variant, flags, SYNTHETIC_ERRNO(EINVAL), "JSON field '%s' is not a boolean.", strna(name));

        *b = json_variant_boolean(variant);
        return 0;
}