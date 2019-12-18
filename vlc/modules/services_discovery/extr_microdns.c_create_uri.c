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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char const*,char*,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
create_uri( const char *psz_protocol, const char *psz_ip, bool b_ipv6,
            uint16_t i_port )
{
    char *psz_uri;

    return asprintf( &psz_uri, "%s://%s%s%s:%u", psz_protocol,
                     b_ipv6 ? "[" : "", psz_ip, b_ipv6 ? "]" : "",
                     i_port ) < 0 ? NULL : psz_uri;
}