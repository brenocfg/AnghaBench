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
typedef  int JsonDispatchFlags ;

/* Variables and functions */
 int JSON_DEBUG ; 
 int /*<<< orphan*/  json_log (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char const*) ; 
 char* json_variant_string (int /*<<< orphan*/ *) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int oci_rootfs_propagation(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        const char *s;

        s = json_variant_string(v);

        if (streq(s, "shared"))
                return 0;

        json_log(v, flags|JSON_DEBUG, 0, "Ignoring rootfsPropagation setting '%s'.", s);
        return 0;
}