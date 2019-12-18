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
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  assert (unsigned int*) ; 
 int json_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ json_variant_unsigned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strna (char const*) ; 

__attribute__((used)) static int oci_console_dimension(const char *name, JsonVariant *variant, JsonDispatchFlags flags, void *userdata) {
        unsigned *u = userdata;
        uintmax_t k;

        assert(u);

        k = json_variant_unsigned(variant);
        if (k == 0)
                return json_log(variant, flags, SYNTHETIC_ERRNO(ERANGE),
                                "Console size field '%s' is too small.", strna(name));
        if (k > USHRT_MAX) /* TIOCSWINSZ's struct winsize uses "unsigned short" for width and height */
                return json_log(variant, flags, SYNTHETIC_ERRNO(ERANGE),
                                "Console size field '%s' is too large.", strna(name));

        *u = (unsigned) k;
        return 0;
}