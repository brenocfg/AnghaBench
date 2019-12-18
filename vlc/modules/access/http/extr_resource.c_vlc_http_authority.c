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
 int asprintf (char**,char const*,char const*,unsigned int) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static char *vlc_http_authority(const char *host, unsigned port)
{
    static const char *const formats[4] = { "%s", "[%s]", "%s:%u", "[%s]:%u" };
    const bool brackets = strchr(host, ':') != NULL;
    const char *fmt = formats[brackets + 2 * (port != 0)];
    char *authority;

    if (unlikely(asprintf(&authority, fmt, host, port) == -1))
        return NULL;
    return authority;
}