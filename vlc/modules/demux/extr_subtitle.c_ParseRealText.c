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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  text_t ;
struct TYPE_3__ {char* psz_text; scalar_t__ i_stop; scalar_t__ i_start; } ;
typedef  TYPE_1__ subtitle_t ;
typedef  int /*<<< orphan*/  subs_properties_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ ParseRealTime (char*,int*,int*,int*,int*) ; 
 char* TextGetLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TextPreviousLine (int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 char* realloc_or_free (char*,size_t) ; 
 int sscanf (char*,char*,char*,char*,...) ; 
 char* strcasestr (char const*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int ParseRealText( vlc_object_t *p_obj, subs_properties_t *p_props,
                          text_t *txt, subtitle_t *p_subtitle, size_t i_idx )
{
    VLC_UNUSED(p_obj);
    VLC_UNUSED(p_props);
    VLC_UNUSED( i_idx );
    char *psz_text = NULL;

    for( ;; )
    {
        int h1 = 0, m1 = 0, s1 = 0, f1 = 0;
        int h2 = 0, m2 = 0, s2 = 0, f2 = 0;
        const char *s = TextGetLine( txt );
        free( psz_text );

        if( !s )
            return VLC_EGENERIC;

        psz_text = malloc( strlen( s ) + 1 );
        if( !psz_text )
            return VLC_ENOMEM;

        /* Find the good begining. This removes extra spaces at the beginning
           of the line.*/
        char *psz_temp = strcasestr( s, "<time");
        if( psz_temp != NULL )
        {
            char psz_end[12], psz_begin[12];
            /* Line has begin and end */
            if( ( sscanf( psz_temp,
                  "<%*[t|T]ime %*[b|B]egin=\"%11[^\"]\" %*[e|E]nd=\"%11[^\"]%*[^>]%[^\n\r]",
                            psz_begin, psz_end, psz_text) != 3 ) &&
                    /* Line has begin and no end */
                    ( sscanf( psz_temp,
                              "<%*[t|T]ime %*[b|B]egin=\"%11[^\"]\"%*[^>]%[^\n\r]",
                              psz_begin, psz_text ) != 2) )
                /* Line is not recognized */
            {
                continue;
            }

            /* Get the times */
            int64_t i_time = ParseRealTime( psz_begin, &h1, &m1, &s1, &f1 );
            p_subtitle->i_start = i_time >= 0 ? i_time : 0;

            i_time = ParseRealTime( psz_end, &h2, &m2, &s2, &f2 );
            p_subtitle->i_stop = i_time >= 0 ? i_time : -1;
            break;
        }
    }

    /* Get the following Lines */
    for( ;; )
    {
        const char *s = TextGetLine( txt );

        if( !s )
        {
            free( psz_text );
            return VLC_EGENERIC;
        }

        size_t i_len = strlen( s );
        if( i_len == 0 ) break;

        if( strcasestr( s, "<time" ) ||
            strcasestr( s, "<clear/") )
        {
            TextPreviousLine( txt );
            break;
        }

        size_t i_old = strlen( psz_text );

        psz_text = realloc_or_free( psz_text, i_old + i_len + 1 + 1 );
        if( !psz_text )
            return VLC_ENOMEM;

        strcat( psz_text, s );
        strcat( psz_text, "\n" );
    }

    /* Remove the starting ">" that remained after the sscanf */
    memmove( &psz_text[0], &psz_text[1], strlen( psz_text ) );

    p_subtitle->psz_text = psz_text;

    return VLC_SUCCESS;
}