#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  text_t ;
struct TYPE_5__ {scalar_t__ i_start; scalar_t__ i_stop; char* psz_text; } ;
typedef  TYPE_1__ subtitle_t ;
typedef  int /*<<< orphan*/  subs_properties_t ;

/* Variables and functions */
 char* TextGetLine (int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 char* realloc_or_free (char*,size_t) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 char* strdup (char*) ; 
 size_t strlen (char const*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int ParseSubRipSubViewer( vlc_object_t *p_obj, subs_properties_t *p_props,
                                 text_t *txt, subtitle_t *p_subtitle,
                                 int (* pf_parse_timing)(subtitle_t *, const char *),
                                 bool b_replace_br )
{
    VLC_UNUSED(p_obj);
    VLC_UNUSED(p_props);
    char    *psz_text;

    for( ;; )
    {
        const char *s = TextGetLine( txt );

        if( !s )
            return VLC_EGENERIC;

        if( pf_parse_timing( p_subtitle, s) == VLC_SUCCESS &&
            p_subtitle->i_start < p_subtitle->i_stop )
        {
            break;
        }
    }

    /* Now read text until an empty line */
    psz_text = strdup("");
    if( !psz_text )
        return VLC_ENOMEM;

    for( ;; )
    {
        const char *s = TextGetLine( txt );
        size_t i_len;
        size_t i_old;

        i_len = s ? strlen( s ) : 0;
        if( i_len <= 0 )
        {
            p_subtitle->psz_text = psz_text;
            return VLC_SUCCESS;
        }

        i_old = strlen( psz_text );
        psz_text = realloc_or_free( psz_text, i_old + i_len + 1 + 1 );
        if( !psz_text )
        {
            return VLC_ENOMEM;
        }
        strcat( psz_text, s );
        strcat( psz_text, "\n" );

        /* replace [br] by \n */
        if( b_replace_br )
        {
            char *p;

            while( ( p = strstr( psz_text, "[br]" ) ) )
            {
                *p++ = '\n';
                memmove( p, &p[3], strlen(&p[3])+1 );
            }
        }
    }
}