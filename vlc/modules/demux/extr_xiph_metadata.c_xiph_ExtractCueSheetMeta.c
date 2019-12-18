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
 char* malloc (int) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char const*,int) ; 

__attribute__((used)) static char * xiph_ExtractCueSheetMeta( const char *psz_line,
                                        const char *psz_tag, int i_tag,
                                        bool b_quoted )
{
    if( !strncasecmp( psz_line, psz_tag, i_tag ) )
    {
        if( !b_quoted )
            return strdup( &psz_line[i_tag] );

        /* Unquote string value */
        char *psz_value = malloc( strlen( psz_line ) - i_tag + 1 );
        if( psz_value )
        {
            char *psz_out = psz_value;
            psz_line += i_tag;
            bool b_escaped = false;
            while( *psz_line )
            {
                switch( *psz_line )
                {
                    case '\\':
                        if( b_escaped )
                        {
                            b_escaped = false;
                            *(psz_out++) = *psz_line;
                        }
                        else
                        {
                            b_escaped = true;
                        }
                        break;
                    case '"':
                        if( b_escaped )
                        {
                            b_escaped = false;
                            *(psz_out++) = *psz_line;
                        }
                        break;
                    default:
                        *(psz_out++) = *psz_line;
                        break;
                }
                psz_line++;
            }
            *psz_out = 0;
            return psz_value;
        }
    }
    return NULL;
}