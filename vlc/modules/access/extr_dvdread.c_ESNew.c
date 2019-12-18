#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/ * palette; } ;
struct TYPE_13__ {TYPE_2__ spu; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_sar_den; int /*<<< orphan*/  i_sar_num; } ;
struct TYPE_17__ {scalar_t__ i_cat; void* psz_language; TYPE_3__ subs; TYPE_1__ video; } ;
struct TYPE_14__ {int b_configured; TYPE_9__ fmt; int /*<<< orphan*/  es; } ;
typedef  TYPE_4__ ps_track_t ;
typedef  char i_lang ;
struct TYPE_15__ {int /*<<< orphan*/  out; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ demux_t ;
struct TYPE_16__ {int /*<<< orphan*/  clut; int /*<<< orphan*/  i_sar_den; int /*<<< orphan*/  i_sar_num; TYPE_4__* tk; } ;
typedef  TYPE_6__ demux_sys_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 scalar_t__ SPU_ES ; 
 int /*<<< orphan*/  SPU_PALETTE_DEFINED ; 
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  es_out_Add (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_5__*,char*,int) ; 
 size_t ps_id_to_tk (int) ; 
 scalar_t__ ps_track_fill (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* strdup (char*) ; 

__attribute__((used)) static void ESNew( demux_t *p_demux, int i_id, int i_lang )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    ps_track_t  *tk = &p_sys->tk[ps_id_to_tk(i_id)];
    char psz_language[3];

    if( tk->b_configured ) return;

    if( ps_track_fill( tk, 0, i_id, NULL, 0, true ) )
    {
        msg_Warn( p_demux, "unknown codec for id=0x%x", i_id );
        return;
    }

    psz_language[0] = psz_language[1] = psz_language[2] = 0;
    if( i_lang && i_lang != 0xffff )
    {
        psz_language[0] = (i_lang >> 8)&0xff;
        psz_language[1] = (i_lang     )&0xff;
    }

    /* Add a new ES */
    if( tk->fmt.i_cat == VIDEO_ES )
    {
        tk->fmt.video.i_sar_num = p_sys->i_sar_num;
        tk->fmt.video.i_sar_den = p_sys->i_sar_den;
    }
    else if( tk->fmt.i_cat == AUDIO_ES )
    {
#if 0
        int i_audio = -1;
        /* find the audio number PLEASE find another way */
        if( (i_id&0xbdf8) == 0xbd88 )       /* dts */
        {
            i_audio = i_id&0x07;
        }
        else if( (i_id&0xbdf0) == 0xbd80 )  /* a52 */
        {
            i_audio = i_id&0xf;
        }
        else if( (i_id&0xbdf0) == 0xbda0 )  /* lpcm */
        {
            i_audio = i_id&0x1f;
        }
        else if( ( i_id&0xe0 ) == 0xc0 )    /* mpga */
        {
            i_audio = i_id&0x1f;
        }
#endif

        if( psz_language[0] ) tk->fmt.psz_language = strdup( psz_language );
    }
    else if( tk->fmt.i_cat == SPU_ES )
    {
        /* Palette */
        tk->fmt.subs.spu.palette[0] = SPU_PALETTE_DEFINED;
        memcpy( &tk->fmt.subs.spu.palette[1], p_sys->clut,
                16 * sizeof( uint32_t ) );

        if( psz_language[0] ) tk->fmt.psz_language = strdup( psz_language );
    }

    tk->es = es_out_Add( p_demux->out, &tk->fmt );
    tk->b_configured = true;
}