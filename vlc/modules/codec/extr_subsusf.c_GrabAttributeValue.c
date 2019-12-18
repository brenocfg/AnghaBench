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
 char* strcasestr (char const*,char const*) ; 
 char* strchr (char const*,char) ; 
 int strcspn (char*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strndup (char*,int) ; 

__attribute__((used)) static char *GrabAttributeValue( const char *psz_attribute,
                                 const char *psz_tag_start )
{
    if( psz_attribute && psz_tag_start )
    {
        char *psz_tag_end = strchr( psz_tag_start, '>' );
        char *psz_found   = strcasestr( psz_tag_start, psz_attribute );

        if( psz_found )
        {
            psz_found += strlen( psz_attribute );

            if(( *(psz_found++) == '=' ) &&
               ( *(psz_found++) == '\"' ))
            {
                if( psz_found < psz_tag_end )
                {
                    int   i_len = strcspn( psz_found, "\"" );
                    return strndup( psz_found, i_len );
                }
            }
        }
    }
    return NULL;
}