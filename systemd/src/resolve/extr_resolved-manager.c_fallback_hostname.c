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

/* Variables and functions */
 char const* FALLBACK_HOSTNAME ; 
 scalar_t__ is_localhost (char const*) ; 

__attribute__((used)) static const char *fallback_hostname(void) {

        /* Determine the fall back hostname. For exposing this system to the outside world, we cannot have it to be
         * "localhost" even if that's the compiled in hostname. In this case, let's revert to "linux" instead. */

        if (is_localhost(FALLBACK_HOSTNAME))
                return "linux";

        return FALLBACK_HOSTNAME;
}