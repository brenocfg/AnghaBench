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
typedef  int usec_t ;
typedef  int uintmax_t ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int UINT64_MAX ; 
 int USEC_PER_SEC ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int json_variant_unsigned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oci_hook_timeout(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {
        usec_t *u = userdata;
        uintmax_t k;

        k = json_variant_unsigned(v);
        if (k == 0 || k > (UINT64_MAX-1)/USEC_PER_SEC)
                return json_log(v, flags, SYNTHETIC_ERRNO(ERANGE),
                                "Hook timeout value out of range.");

        *u = k * USEC_PER_SEC;
        return 0;
}