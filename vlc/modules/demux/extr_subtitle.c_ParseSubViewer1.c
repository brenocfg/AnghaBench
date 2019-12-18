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
struct TYPE_3__ {int i_stop; char* psz_text; void* i_start; } ;
typedef  TYPE_1__ subtitle_t ;
typedef  int /*<<< orphan*/  subs_properties_t ;

/* Variables and functions */
 char* TextGetLine (int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 int sscanf (char*,char*,int*,int*,int*) ; 
 char* strdup (char*) ; 
 void* vlc_tick_from_sec (int) ; 

__attribute__((used)) static int ParseSubViewer1( vlc_object_t *p_obj, subs_properties_t *p_props,
                            text_t *txt, subtitle_t *p_subtitle, size_t i_idx )
{
    VLC_UNUSED(p_obj);
    VLC_UNUSED(p_props);
    VLC_UNUSED( i_idx );
    char *psz_text;

    for( ;; )
    {
        int h1, m1, s1;
        int h2, m2, s2;
        char *s = TextGetLine( txt );

        if( !s )
            return VLC_EGENERIC;

        if( sscanf( s, "[%d:%d:%d]", &h1, &m1, &s1 ) == 3 )
        {
            p_subtitle->i_start = vlc_tick_from_sec( h1 * 3600 + m1 * 60 + s1 );

            s = TextGetLine( txt );
            if( !s )
                return VLC_EGENERIC;

            psz_text = strdup( s );
            if( !psz_text )
                return VLC_ENOMEM;

            s = TextGetLine( txt );
            if( !s )
            {
                free( psz_text );
                return VLC_EGENERIC;
            }

            if( sscanf( s, "[%d:%d:%d]", &h2, &m2, &s2 ) == 3 )
                p_subtitle->i_stop  = vlc_tick_from_sec( h2 * 3600 + m2 * 60 + s2 );
            else
                p_subtitle->i_stop  = -1;

            break;
        }
    }

    p_subtitle->psz_text = psz_text;

    return VLC_SUCCESS;
}