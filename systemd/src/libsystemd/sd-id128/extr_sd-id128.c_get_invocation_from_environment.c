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
typedef  int /*<<< orphan*/  sd_id128_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int sd_id128_from_string (char const*,int /*<<< orphan*/ *) ; 
 char* secure_getenv (char*) ; 

__attribute__((used)) static int get_invocation_from_environment(sd_id128_t *ret) {
        const char *e;

        assert(ret);

        e = secure_getenv("INVOCATION_ID");
        if (!e)
                return -ENXIO;

        return sd_id128_from_string(e, ret);
}