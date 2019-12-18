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
 char* cookie_get_attribute_value (char const*,char*) ; 
 int /*<<< orphan*/  memmove (char*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 int strspn (char*,char*) ; 

__attribute__((used)) static char *cookie_get_domain( const char *cookie )
{
    char *domain = cookie_get_attribute_value( cookie, "domain" );
    if( domain == NULL )
        return NULL;

    if( domain[0] == '.' )
    {
        const char *real_domain = domain + strspn( domain, "." );
        memmove( domain, real_domain, strlen( real_domain ) + 1 );
    }
    return domain;
}