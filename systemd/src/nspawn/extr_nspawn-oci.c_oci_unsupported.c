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
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_variant_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_variant_type_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int oci_unsupported(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        return json_log(v, flags, SYNTHETIC_ERRNO(EOPNOTSUPP),
                        "Unsupported OCI element '%s' of type '%s'.", name, json_variant_type_to_string(json_variant_type(v)));
}