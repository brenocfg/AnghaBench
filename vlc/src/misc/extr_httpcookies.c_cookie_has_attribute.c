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
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strspn (char const*,char*) ; 
 int /*<<< orphan*/  vlc_ascii_strncasecmp (char const*,char const*,size_t) ; 

__attribute__((used)) static bool cookie_has_attribute( const char *cookie, const char *attr )
{
    size_t attrlen = strlen(attr);
    const char * str = strchr(cookie, ';');
    while( str )
    {
        /* skip ; and blank */
        str++;
        str += strspn( str, " " );

        if( !vlc_ascii_strncasecmp( str, attr, attrlen )
         && (str[attrlen] == '=' || str[attrlen] == ';' || str[attrlen] == '\0') )
            return true;

        str = strchr(str, ';');
    }
    return false;
}