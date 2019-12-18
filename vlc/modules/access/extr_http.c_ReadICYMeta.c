#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {scalar_t__ p_input_item; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_7__ {char* psz_icy_title; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 char* EnsureUTF8 (char*) ; 
 scalar_t__ ReadData (TYPE_1__*,int*,int*,int const) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_item_SetMeta (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 char* malloc (int const) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char*) ; 
 char* strcasestr (char*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  vlc_meta_NowPlaying ; 

__attribute__((used)) static int ReadICYMeta( stream_t *p_access )
{
    access_sys_t *p_sys = p_access->p_sys;

    uint8_t buffer;
    char *p, *psz_meta;
    int i_read;

    /* Read meta data length */
    if( ReadData( p_access, &i_read, &buffer, 1 ) )
        return VLC_EGENERIC;
    if( i_read != 1 )
        return VLC_EGENERIC;
    const int i_size = buffer << 4;
    /* msg_Dbg( p_access, "ICY meta size=%u", i_size); */

    psz_meta = malloc( i_size + 1 );
    for( i_read = 0; i_read < i_size; )
    {
        int i_tmp;
        if( ReadData( p_access, &i_tmp, (uint8_t *)&psz_meta[i_read], i_size - i_read ) || i_tmp <= 0 )
        {
            free( psz_meta );
            return VLC_EGENERIC;
        }
        i_read += i_tmp;
    }
    psz_meta[i_read] = '\0'; /* Just in case */

    /* msg_Dbg( p_access, "icy-meta=%s", psz_meta ); */

    /* Now parse the meta */
    /* Look for StreamTitle= */
    p = strcasestr( (char *)psz_meta, "StreamTitle=" );
    if( p )
    {
        p += strlen( "StreamTitle=" );
        if( *p == '\'' || *p == '"' )
        {
            char closing[] = { p[0], ';', '\0' };
            char *psz = strstr( &p[1], closing );
            if( !psz )
                psz = strchr( &p[1], ';' );

            if( psz ) *psz = '\0';
            p++;
        }
        else
        {
            char *psz = strchr( p, ';' );
            if( psz ) *psz = '\0';
        }

        if( !p_sys->psz_icy_title ||
            strcmp( p_sys->psz_icy_title, p ) )
        {
            free( p_sys->psz_icy_title );
            char *psz_tmp = strdup( p );
            p_sys->psz_icy_title = EnsureUTF8( psz_tmp );
            if( !p_sys->psz_icy_title )
                free( psz_tmp );

            msg_Dbg( p_access, "New Icy-Title=%s", p_sys->psz_icy_title );
            if( p_access->p_input_item )
                input_item_SetMeta( p_access->p_input_item, vlc_meta_NowPlaying,
                                    p_sys->psz_icy_title );
        }
    }
    free( psz_meta );

    return VLC_SUCCESS;
}