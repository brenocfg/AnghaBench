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
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  strcspn (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static char *StripTags( char *psz_subtitle )
{
    char *psz_text_start;
    char *psz_text;

    psz_text = psz_text_start = malloc( strlen( psz_subtitle ) + 1 );
    if( !psz_text_start )
        return NULL;

    while( *psz_subtitle )
    {
        /* Mask out any pre-existing LFs in the subtitle */
        if( *psz_subtitle == '\n' )
            *psz_subtitle = ' ';

        if( *psz_subtitle == '<' )
        {
            if( strncasecmp( psz_subtitle, "<br/>", 5 ) == 0 )
                *psz_text++ = '\n';

            psz_subtitle += strcspn( psz_subtitle, ">" );
        }
        else if( *psz_subtitle == '&' )
        {
            if( !strncasecmp( psz_subtitle, "&lt;", 4 ))
            {
                *psz_text++ = '<';
                psz_subtitle += strcspn( psz_subtitle, ";" );
            }
            else if( !strncasecmp( psz_subtitle, "&gt;", 4 ))
            {
                *psz_text++ = '>';
                psz_subtitle += strcspn( psz_subtitle, ";" );
            }
            else if( !strncasecmp( psz_subtitle, "&amp;", 5 ))
            {
                *psz_text++ = '&';
                psz_subtitle += strcspn( psz_subtitle, ";" );
            }
            else if( !strncasecmp( psz_subtitle, "&quot;", 6 ))
            {
                *psz_text++ = '\"';
                psz_subtitle += strcspn( psz_subtitle, ";" );
            }
            else
            {
                /* Assume it is just a normal ampersand */
                *psz_text++ = '&';
            }
        }
        else
        {
            *psz_text++ = *psz_subtitle;
        }

        /* Security fix: Account for the case where input ends early */
        if( *psz_subtitle == '\0' ) break;

        psz_subtitle++;
    }
    *psz_text++ = '\0';

    char *psz = realloc( psz_text_start, psz_text - psz_text_start );
    return likely(psz != NULL) ? psz : psz_text_start;
}