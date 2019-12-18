#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  psz_url ;
struct TYPE_10__ {int* pb_gain; float* pf_gain; int* pb_peak; float* pf_peak; } ;
struct TYPE_11__ {TYPE_1__ audio_replay_gain; } ;
typedef  TYPE_2__ es_format_t ;
struct TYPE_12__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_13__ {int i_attachments; int i_seekpoints; int /*<<< orphan*/  updates; int /*<<< orphan*/ * p_meta; TYPE_6__** attachments; int /*<<< orphan*/  pp_seekpoints; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_14__ {char* psz_name; } ;

/* Variables and functions */
 int AUDIO_REPLAY_GAIN_MAX ; 
 int /*<<< orphan*/  INPUT_UPDATE_TITLE_LIST ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,int,float) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  vlc_meta_ArtworkURL ; 
 int /*<<< orphan*/  vlc_meta_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vorbis_ParseComment (TYPE_2__*,int /*<<< orphan*/ **,void const*,unsigned int,int*,TYPE_6__***,int*,int*,int*,int /*<<< orphan*/ *,float**,float**) ; 

__attribute__((used)) static void Ogg_ExtractComments( demux_t *p_demux, es_format_t *p_fmt,
                                 const void *p_headers, unsigned i_headers )
{
    demux_sys_t *p_ogg = p_demux->p_sys;
    int i_cover_score = 0;
    int i_cover_idx = 0;
    float pf_replay_gain[AUDIO_REPLAY_GAIN_MAX];
    float pf_replay_peak[AUDIO_REPLAY_GAIN_MAX];
    for(int i=0; i< AUDIO_REPLAY_GAIN_MAX; i++ )
    {
        pf_replay_gain[i] = 0;
        pf_replay_peak[i] = 0;
    }
    vorbis_ParseComment( p_fmt, &p_ogg->p_meta, p_headers, i_headers,
                         &p_ogg->i_attachments, &p_ogg->attachments,
                         &i_cover_score, &i_cover_idx,
                         &p_ogg->i_seekpoints, &p_ogg->pp_seekpoints,
                         &pf_replay_gain, &pf_replay_peak );
    if( p_ogg->p_meta != NULL && i_cover_idx < p_ogg->i_attachments )
    {
        char psz_url[128];
        snprintf( psz_url, sizeof(psz_url), "attachment://%s",
                  p_ogg->attachments[i_cover_idx]->psz_name );
        vlc_meta_Set( p_ogg->p_meta, vlc_meta_ArtworkURL, psz_url );
    }

    for ( int i=0; i<AUDIO_REPLAY_GAIN_MAX;i++ )
    {
        if ( pf_replay_gain[i] != 0 )
        {
            p_fmt->audio_replay_gain.pb_gain[i] = true;
            p_fmt->audio_replay_gain.pf_gain[i] = pf_replay_gain[i];
            msg_Dbg( p_demux, "setting replay gain %d to %f", i, pf_replay_gain[i] );
        }
        if ( pf_replay_peak[i] != 0 )
        {
            p_fmt->audio_replay_gain.pb_peak[i] = true;
            p_fmt->audio_replay_gain.pf_peak[i] = pf_replay_peak[i];
            msg_Dbg( p_demux, "setting replay peak %d to %f", i, pf_replay_gain[i] );
        }
    }

    if( p_ogg->i_seekpoints > 1 )
    {
        p_ogg->updates |= INPUT_UPDATE_TITLE_LIST;
    }
}