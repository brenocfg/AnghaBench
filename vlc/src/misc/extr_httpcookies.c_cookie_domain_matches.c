#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* psz_domain; scalar_t__ b_host_only; } ;
typedef  TYPE_1__ http_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 size_t strspn (char const*,char*) ; 
 scalar_t__ vlc_ascii_strcasecmp (char const*,char const*) ; 

__attribute__((used)) static bool cookie_domain_matches( const http_cookie_t *cookie,
                                   const char *host )
{
    // TODO: should convert domain names to punycode before comparing

    if (host == NULL)
        return false;
    if ( vlc_ascii_strcasecmp(cookie->psz_domain, host) == 0 )
        return true;
    else if ( cookie->b_host_only )
        return false;

    size_t host_len = strlen(host);
    size_t cookie_domain_len = strlen(cookie->psz_domain);
    bool is_suffix = false, has_dot_before_suffix = false;

    if( host_len > cookie_domain_len )
    {
        size_t i = host_len - cookie_domain_len;

        is_suffix = vlc_ascii_strcasecmp( &host[i], cookie->psz_domain ) == 0;
        has_dot_before_suffix = host[i-1] == '.';
    }

    bool host_is_ipv4 = strspn(host, "0123456789.") == host_len;
    bool host_is_ipv6 = strchr(host, ':') != NULL;
    return is_suffix && has_dot_before_suffix &&
        !( host_is_ipv4 || host_is_ipv6 );
}