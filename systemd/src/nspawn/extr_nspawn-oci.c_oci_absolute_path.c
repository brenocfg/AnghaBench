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
 int /*<<< orphan*/  assert (char**) ; 
 int free_and_strdup_warn (char**,char const*) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 char* json_variant_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_is_absolute (char const*) ; 
 int /*<<< orphan*/  strna (char const*) ; 

__attribute__((used)) static int oci_absolute_path(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        char **p = userdata;
        const char *n;

        assert(p);

        n = json_variant_string(v);

        if (!path_is_absolute(n))
                return json_log(v, flags, SYNTHETIC_ERRNO(EINVAL),
                                "Path in JSON field '%s' is not absolute: %s", strna(name), n);

        return free_and_strdup_warn(p, n);
}