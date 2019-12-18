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
 char* LanguageGetCode (char*) ; 
 int /*<<< orphan*/  TAB_APPEND (int,char**,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char **LanguageSplit( const char *psz_langs )
{
    char *psz_dup;
    char *psz_parser;
    char **ppsz = NULL;
    int i_psz = 0;

    if( psz_langs == NULL ) return NULL;

    psz_parser = psz_dup = strdup(psz_langs);

    while( psz_parser && *psz_parser )
    {
        char *psz;
        char *psz_code;

        psz = strchr(psz_parser, ',' );
        if( psz ) *psz++ = '\0';

        if( !strcmp( psz_parser, "any" ) )
        {
            TAB_APPEND( i_psz, ppsz, strdup("any") );
        }
        else if( !strcmp( psz_parser, "none" ) )
        {
            TAB_APPEND( i_psz, ppsz, strdup("none") );
        }
        else
        {
            psz_code = LanguageGetCode( psz_parser );
            if( strcmp( psz_code, "??" ) )
            {
                TAB_APPEND( i_psz, ppsz, psz_code );
            }
            else
            {
                free( psz_code );
            }
        }

        psz_parser = psz;
    }

    if( i_psz )
    {
        TAB_APPEND( i_psz, ppsz, NULL );
    }

    free( psz_dup );
    return ppsz;
}