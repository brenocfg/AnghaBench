#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i_channel; int /*<<< orphan*/ * p_es; } ;
typedef  TYPE_1__ hdsdi_audio_t ;
struct TYPE_6__ {int /*<<< orphan*/  out; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_7__ {TYPE_1__* p_audios; int /*<<< orphan*/ * p_es_video; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int MAX_AUDIOS ; 
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void StopDecode( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    es_out_Del( p_demux->out, p_sys->p_es_video );

    for ( int i = 0; i < MAX_AUDIOS; i++ )
    {
        hdsdi_audio_t *p_audio = &p_sys->p_audios[i];
        if ( p_audio->i_channel != -1 && p_audio->p_es != NULL )
        {
            es_out_Del( p_demux->out, p_audio->p_es );
            p_audio->p_es = NULL;
        }
    }
}