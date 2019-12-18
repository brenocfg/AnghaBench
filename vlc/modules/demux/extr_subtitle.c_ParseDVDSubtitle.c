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
struct TYPE_3__ {int i_stop; char* psz_text; scalar_t__ i_start; } ;
typedef  TYPE_1__ subtitle_t ;
typedef  int /*<<< orphan*/  subs_properties_t ;

/* Variables and functions */
 char* TextGetLine (int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  VLC_UNUSED (size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* realloc_or_free (char*,int) ; 
 int sscanf (char const*,char*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 char* strdup (char*) ; 
 int strlen (char const*) ; 
 scalar_t__ vlc_tick_from_sec (int) ; 

__attribute__((used)) static int ParseDVDSubtitle(vlc_object_t *p_obj, subs_properties_t *p_props,
                            text_t *txt, subtitle_t *p_subtitle, size_t i_idx )
{
    VLC_UNUSED(p_obj);
    VLC_UNUSED(p_props);
    VLC_UNUSED( i_idx );
    char *psz_text;

    for( ;; )
    {
        const char *s = TextGetLine( txt );
        int h1, m1, s1, c1;

        if( !s )
            return VLC_EGENERIC;

        if( sscanf( s,
                    "{T %d:%d:%d:%d",
                    &h1, &m1, &s1, &c1 ) == 4 )
        {
            p_subtitle->i_start = vlc_tick_from_sec( h1 * 3600 + m1 * 60 + s1 ) +
                                  VLC_TICK_FROM_MS( c1 * 10 );
            p_subtitle->i_stop = -1;
            break;
        }
    }

    /* Now read text until a line containing "}" */
    psz_text = strdup("");
    if( !psz_text )
        return VLC_ENOMEM;
    for( ;; )
    {
        const char *s = TextGetLine( txt );
        int i_len;
        int i_old;

        if( !s )
        {
            free( psz_text );
            return VLC_EGENERIC;
        }

        i_len = strlen( s );
        if( i_len == 1 && s[0] == '}')
        {
            p_subtitle->psz_text = psz_text;
            return VLC_SUCCESS;
        }

        i_old = strlen( psz_text );
        psz_text = realloc_or_free( psz_text, i_old + i_len + 1 + 1 );
        if( !psz_text )
            return VLC_ENOMEM;
        strcat( psz_text, s );
        strcat( psz_text, "\n" );
    }
}