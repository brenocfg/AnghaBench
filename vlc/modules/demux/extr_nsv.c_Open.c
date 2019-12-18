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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  force; } ;
struct TYPE_7__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; TYPE_3__* p_sys; TYPE_1__ obj; int /*<<< orphan*/  s; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_8__ {int b_start_record; scalar_t__ i_pcr_inc; scalar_t__ i_time; scalar_t__ i_pcr; int /*<<< orphan*/ * p_sub; int /*<<< orphan*/  fmt_sub; int /*<<< orphan*/ * p_video; int /*<<< orphan*/  fmt_video; int /*<<< orphan*/ * p_audio; int /*<<< orphan*/  fmt_audio; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Demux ; 
 scalar_t__ ReSynch (TYPE_2__*) ; 
 int /*<<< orphan*/  SPU_ES ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* malloc (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    demux_t     *p_demux = (demux_t*)p_this;
    demux_sys_t *p_sys;

    const uint8_t *p_peek;

    if( vlc_stream_Peek( p_demux->s, &p_peek, 8 ) < 8 )
        return VLC_EGENERIC;

    if( memcmp( p_peek, "NSVf", 4 ) && memcmp( p_peek, "NSVs", 4 ) )
    {
       /* In case we had force this demuxer we try to resynch */
        if( !p_demux->obj.force || ReSynch( p_demux ) )
            return VLC_EGENERIC;
    }

    p_sys = malloc( sizeof( demux_sys_t ) );
    if( unlikely(p_sys == NULL) )
        return VLC_ENOMEM;

    /* Fill p_demux field */
    p_demux->p_sys = p_sys;
    p_demux->pf_demux = Demux;
    p_demux->pf_control = Control;

    es_format_Init( &p_sys->fmt_audio, AUDIO_ES, 0 );
    p_sys->p_audio = NULL;

    es_format_Init( &p_sys->fmt_video, VIDEO_ES, 0 );
    p_sys->p_video = NULL;

    es_format_Init( &p_sys->fmt_sub, SPU_ES, 0 );
    p_sys->p_sub = NULL;

    p_sys->i_pcr   = 0;
    p_sys->i_time  = 0;
    p_sys->i_pcr_inc = 0;

    p_sys->b_start_record = false;

    return VLC_SUCCESS;
}