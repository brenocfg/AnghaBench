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
typedef  char* JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (char**) ; 
 int free_and_strdup (char**,int /*<<< orphan*/ ) ; 
 int json_log (char**,int /*<<< orphan*/ ,int,char*,...) ; 
 scalar_t__ json_variant_is_null (char**) ; 
 int /*<<< orphan*/  json_variant_is_string (char**) ; 
 int /*<<< orphan*/  json_variant_string (char**) ; 
 char* mfree (char*) ; 
 int /*<<< orphan*/  strna (char const*) ; 

int json_dispatch_string(const char *name, JsonVariant *variant, JsonDispatchFlags flags, void *userdata) {
        char **s = userdata;
        int r;

        assert(variant);
        assert(s);

        if (json_variant_is_null(variant)) {
                *s = mfree(*s);
                return 0;
        }

        if (!json_variant_is_string(variant))
                return json_log(variant, flags, SYNTHETIC_ERRNO(EINVAL), "JSON field '%s' is not a string.", strna(name));

        r = free_and_strdup(s, json_variant_string(variant));
        if (r < 0)
                return json_log(variant, flags, r, "Failed to allocate string: %m");

        return 0;
}