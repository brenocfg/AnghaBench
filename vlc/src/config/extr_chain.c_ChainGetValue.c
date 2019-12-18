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
 char* ChainGetEnd (char const*) ; 
 int /*<<< orphan*/  SKIPSPACE (char const*) ; 
 int /*<<< orphan*/  SKIPTRAILINGSPACE (char const*,char const*) ; 
 int /*<<< orphan*/  config_StringUnescape (char*) ; 
 char* strndup (char const*,int) ; 

__attribute__((used)) static char *ChainGetValue( const char **ppsz_string )
{
    const char *p = *ppsz_string;

    char *psz_value = NULL;
    const char *end;
    bool b_keep_brackets = (*p == '{');

    if( *p == '=' )
        p++;

    end = ChainGetEnd( p );
    if( end <= p )
    {
        psz_value = NULL;
    }
    else
    {
        /* Skip heading and trailing spaces.
         * This ain't necessary but will avoid simple
         * user mistakes. */
        SKIPSPACE( p );
    }

    if( end <= p )
    {
        psz_value = NULL;
    }
    else
    {
        if( *p == '\'' || *p == '"' || ( !b_keep_brackets && *p == '{' ) )
        {
            p++;

            if( *(end-1) != '\'' && *(end-1) == '"' )
                SKIPTRAILINGSPACE( p, end );

            if( end - 1 <= p )
                psz_value = NULL;
            else
                psz_value = strndup( p, end -1 - p );
        }
        else
        {
            SKIPTRAILINGSPACE( p, end );
            if( end <= p )
                psz_value = NULL;
            else
                psz_value = strndup( p, end - p );
        }
    }

    /* */
    if( psz_value )
        config_StringUnescape( psz_value );

    /* */
    *ppsz_string = end;
    return psz_value;
}