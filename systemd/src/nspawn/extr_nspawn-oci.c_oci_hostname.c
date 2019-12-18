#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hostname; } ;
typedef  TYPE_1__ Settings ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (char const*) ; 
 int free_and_strdup_warn (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  hostname_is_valid (char const*,int) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 char* json_variant_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oci_hostname(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        Settings *s = userdata;
        const char *n;

        assert(s);

        assert_se(n = json_variant_string(v));

        if (!hostname_is_valid(n, false))
                return json_log(v, flags, SYNTHETIC_ERRNO(EINVAL),
                                "Hostname string is not a valid hostname: %s", n);

        return free_and_strdup_warn(&s->hostname, n);
}