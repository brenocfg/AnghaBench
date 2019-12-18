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
 char const* SYSTEMD_LANGUAGE_FALLBACK_MAP ; 
 char* getenv (char*) ; 

__attribute__((used)) static const char* systemd_language_fallback_map(void) {
        const char* s;

        s = getenv("SYSTEMD_LANGUAGE_FALLBACK_MAP");
        if (s)
                return s;

        return SYSTEMD_LANGUAGE_FALLBACK_MAP;
}