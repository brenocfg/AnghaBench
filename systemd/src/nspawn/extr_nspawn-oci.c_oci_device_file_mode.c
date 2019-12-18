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
typedef  int mode_t ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int*) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ json_variant_unsigned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oci_device_file_mode(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        mode_t *mode = userdata, m;
        uintmax_t k;

        assert(mode);

        k = json_variant_unsigned(v);
        m = (mode_t) k;

        if ((m & ~07777) != 0 || (uintmax_t) m != k)
                return json_log(v, flags, SYNTHETIC_ERRNO(ERANGE),
                                "fileMode out of range, refusing.");

        *mode = m;
        return 0;
}