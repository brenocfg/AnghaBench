#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  text_t ;
struct TYPE_7__ {char* psz_text; void* i_stop; void* i_start; } ;
typedef  TYPE_2__ subtitle_t ;
struct TYPE_6__ {int b_inited; double f_total; int i_factor; } ;
struct TYPE_8__ {TYPE_1__ mpsub; } ;
typedef  TYPE_3__ subs_properties_t ;

/* Variables and functions */
 char* TextGetLine (int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* llroundf (float) ; 
 char* malloc (size_t) ; 
 char* realloc_or_free (char*,size_t) ; 
 int sscanf (char const*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 char* strdup (char*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strstr (char const*,char*) ; 
 float us_strtof (char const*,char**) ; 
 float var_GetFloat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_SetFloat (int /*<<< orphan*/ *,char*,float) ; 

__attribute__((used)) static int ParseMPSub( vlc_object_t *p_obj, subs_properties_t *p_props,
                       text_t *txt, subtitle_t *p_subtitle, size_t i_idx )
{
    VLC_UNUSED( i_idx );

    char *psz_text = strdup( "" );

    if( !p_props->mpsub.b_inited )
    {
        p_props->mpsub.f_total = 0.0;
        p_props->mpsub.i_factor = 0;

        p_props->mpsub.b_inited = true;
    }

    for( ;; )
    {
        char p_dummy;
        char *psz_temp;

        const char *s = TextGetLine( txt );
        if( !s )
        {
            free( psz_text );
            return VLC_EGENERIC;
        }

        if( strstr( s, "FORMAT" ) )
        {
            if( sscanf (s, "FORMAT=TIM%c", &p_dummy ) == 1 && p_dummy == 'E')
            {
                p_props->mpsub.i_factor = 100;
                break;
            }

            psz_temp = malloc( strlen(s) );
            if( !psz_temp )
            {
                free( psz_text );
                return VLC_ENOMEM;
            }

            if( sscanf( s, "FORMAT=%[^\r\n]", psz_temp ) )
            {
                float f_fps = us_strtof( psz_temp, NULL );

                if( f_fps > 0.f && var_GetFloat( p_obj, "sub-original-fps" ) <= 0.f )
                    var_SetFloat( p_obj, "sub-original-fps", f_fps );

                p_props->mpsub.i_factor = 1;
                free( psz_temp );
                break;
            }
            free( psz_temp );
        }

        /* Data Lines */
        float f1 = us_strtof( s, &psz_temp );
        if( *psz_temp )
        {
            float f2 = us_strtof( psz_temp, NULL );
            p_props->mpsub.f_total += f1 * p_props->mpsub.i_factor;
            p_subtitle->i_start = llroundf(10000.f * p_props->mpsub.f_total);
            p_props->mpsub.f_total += f2 * p_props->mpsub.i_factor;
            p_subtitle->i_stop = llroundf(10000.f * p_props->mpsub.f_total);
            break;
        }
    }

    for( ;; )
    {
        const char *s = TextGetLine( txt );

        if( !s )
        {
            free( psz_text );
            return VLC_EGENERIC;
        }

        size_t i_len = strlen( s );
        if( i_len == 0 )
            break;

        size_t i_old = strlen( psz_text );

        psz_text = realloc_or_free( psz_text, i_old + i_len + 1 + 1 );
        if( !psz_text )
             return VLC_ENOMEM;

        strcat( psz_text, s );
        strcat( psz_text, "\n" );
    }

    p_subtitle->psz_text = psz_text;
    return VLC_SUCCESS;
}