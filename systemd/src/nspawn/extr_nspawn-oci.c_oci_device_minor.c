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
typedef  scalar_t__ uintmax_t ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_MINOR_VALID (scalar_t__) ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (unsigned int*) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ json_variant_unsigned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oci_device_minor(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        unsigned *u = userdata;
        uintmax_t k;

        assert_se(u);

        k = json_variant_unsigned(v);
        if (!DEVICE_MINOR_VALID(k))
                return json_log(v, flags, SYNTHETIC_ERRNO(ERANGE),
                                "Device minor %ji out of range.", k);

        *u = (unsigned) k;
        return 0;
}