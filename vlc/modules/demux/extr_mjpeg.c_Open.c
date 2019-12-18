#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_9__ {int /*<<< orphan*/  force; } ;
struct TYPE_10__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  out; int /*<<< orphan*/  pf_demux; int /*<<< orphan*/  s; TYPE_3__* p_sys; TYPE_1__ obj; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_11__ {int i_frame_size_estimate; int* p_peek; int b_still; int /*<<< orphan*/ * p_es; int /*<<< orphan*/  fmt; void* i_frame_length; void* i_still_end; scalar_t__ i_level; int /*<<< orphan*/ * psz_separator; int /*<<< orphan*/  i_time; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int CheckMimeHeader (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  Control ; 
 scalar_t__ IsMxpeg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MimeDemux ; 
 int /*<<< orphan*/  MjpgDemux ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_MJPG ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_0 ; 
 void* VLC_TICK_INVALID ; 
 scalar_t__ demux_IsPathExtension (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * es_out_Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 char* stream_ContentType (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 char* strstr (char*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 float var_InheritFloat (TYPE_2__*,char*) ; 
 TYPE_3__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vlc_obj_strdup (int /*<<< orphan*/ *,char*) ; 
 int vlc_stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* vlc_tick_rate_duration (float) ; 

__attribute__((used)) static int Open( vlc_object_t * p_this )
{
    demux_t     *p_demux = (demux_t*)p_this;
    int         i_size;
    bool        b_matched = false;

    if( IsMxpeg( p_demux->s ) && !p_demux->obj.force )
        // let avformat handle this case
        return VLC_EGENERIC;

    demux_sys_t *p_sys = vlc_obj_malloc( p_this, sizeof (*p_sys) );
    if( unlikely(p_sys == NULL) )
        return VLC_ENOMEM;

    p_demux->p_sys      = p_sys;
    p_sys->p_es         = NULL;
    p_sys->i_time       = VLC_TICK_0;
    p_sys->i_level      = 0;

    p_sys->psz_separator = NULL;
    p_sys->i_frame_size_estimate = 15 * 1024;

    char *content_type = stream_ContentType( p_demux->s );
    if ( content_type )
    {
        //FIXME: this is not fully match to RFC
        char* boundary = strstr( content_type, "boundary=" );
        if( boundary )
        {
            boundary += strlen( "boundary=" );
            size_t len = strlen( boundary );
            if( len > 2 && boundary[0] == '"'
                && boundary[len-1] == '"' )
            {
                boundary[len-1] = '\0';
                boundary++;
            }
            p_sys->psz_separator = vlc_obj_strdup( p_this, boundary );
            if( !p_sys->psz_separator )
            {
                free( content_type );
                return VLC_ENOMEM;
            }
        }
        free( content_type );
    }

    b_matched = CheckMimeHeader( p_demux, &i_size);
    if( b_matched )
    {
        p_demux->pf_demux = MimeDemux;
        if( vlc_stream_Read( p_demux->s, NULL, i_size ) < i_size )
            return VLC_EGENERIC;
    }
    else if( i_size == 0 )
    {
        /* 0xffd8 identify a JPEG SOI */
        if( p_sys->p_peek[0] == 0xFF && p_sys->p_peek[1] == 0xD8 )
        {
            msg_Dbg( p_demux, "JPEG SOI marker detected" );
            p_demux->pf_demux = MjpgDemux;
            p_sys->i_level++;
        }
        else
        {
            return VLC_EGENERIC;
        }
    }
    else
    {
        return VLC_EGENERIC;
    }

    /* Frame rate */
    float f_fps = var_InheritFloat( p_demux, "mjpeg-fps" );

    p_sys->i_still_end = VLC_TICK_INVALID;
    if( demux_IsPathExtension( p_demux, ".jpeg" ) ||
        demux_IsPathExtension( p_demux, ".jpg" ) )
    {
        /* Plain JPEG file = single still picture */
        p_sys->b_still = true;
        if( f_fps == 0.f )
            /* Defaults to 1fps */
            f_fps = 1.f;
    }
    else
        p_sys->b_still = false;
    p_sys->i_frame_length = f_fps ? vlc_tick_rate_duration(f_fps) : VLC_TICK_INVALID;

    es_format_Init( &p_sys->fmt, VIDEO_ES, VLC_CODEC_MJPG );

    p_sys->p_es = es_out_Add( p_demux->out, &p_sys->fmt );
    if( unlikely(p_sys->p_es == NULL) )
        return VLC_ENOMEM;

    p_demux->pf_control = Control;
    return VLC_SUCCESS;
}