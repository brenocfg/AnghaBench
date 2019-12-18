#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  p_child; } ;
typedef  TYPE_2__ webvtt_region_t ;
typedef  int /*<<< orphan*/  webvtt_dom_node_t ;
struct TYPE_19__ {int /*<<< orphan*/  psz_region; } ;
struct TYPE_22__ {char* psz_id; int /*<<< orphan*/ * p_parent; TYPE_13__ settings; } ;
typedef  TYPE_3__ webvtt_dom_cue_t ;
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_23__ {scalar_t__ i_type; size_t i_payload; int /*<<< orphan*/  const* p_payload; } ;
typedef  TYPE_4__ mp4_box_iterator_t ;
struct TYPE_24__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ decoder_t ;
struct TYPE_25__ {TYPE_1__* p_root; } ;
typedef  TYPE_6__ decoder_sys_t ;
struct TYPE_20__ {int /*<<< orphan*/  p_child; } ;

/* Variables and functions */
#define  ATOM_iden 130 
#define  ATOM_payl 129 
#define  ATOM_sttg 128 
 scalar_t__ ATOM_vttc ; 
 scalar_t__ ATOM_vttx ; 
 int /*<<< orphan*/  ProcessCue (TYPE_5__*,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mp4_box_iterator_Init (TYPE_4__*,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ mp4_box_iterator_Next (TYPE_4__*) ; 
 void* strndup (char*,size_t) ; 
 int /*<<< orphan*/  webvtt_cue_settings_Parse (TYPE_13__*,char*) ; 
 TYPE_3__* webvtt_dom_cue_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  webvtt_domnode_AppendLast (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  webvtt_region_AddCue (TYPE_2__*,TYPE_3__*) ; 
 TYPE_2__* webvtt_region_GetByID (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ProcessISOBMFF( decoder_t *p_dec,
                           const uint8_t *p_buffer, size_t i_buffer,
                           vlc_tick_t i_start, vlc_tick_t i_stop )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    mp4_box_iterator_t it;
    mp4_box_iterator_Init( &it, p_buffer, i_buffer );
    while( mp4_box_iterator_Next( &it ) )
    {
        if( it.i_type == ATOM_vttc || it.i_type == ATOM_vttx )
        {
            webvtt_dom_cue_t *p_cue = webvtt_dom_cue_New( i_start, i_stop );
            if( !p_cue )
                continue;

            mp4_box_iterator_t vtcc;
            mp4_box_iterator_Init( &vtcc, it.p_payload, it.i_payload );
            while( mp4_box_iterator_Next( &vtcc ) )
            {
                char *psz = NULL;
                switch( vtcc.i_type )
                {
                    case ATOM_iden:
                        free( p_cue->psz_id );
                        p_cue->psz_id = strndup( (char *) vtcc.p_payload, vtcc.i_payload );
                        break;
                    case ATOM_sttg:
                    {
                        psz = strndup( (char *) vtcc.p_payload, vtcc.i_payload );
                        if( psz )
                            webvtt_cue_settings_Parse( &p_cue->settings, psz );
                    } break;
                    case ATOM_payl:
                    {
                        psz = strndup( (char *) vtcc.p_payload, vtcc.i_payload );
                        if( psz )
                            ProcessCue( p_dec, psz, p_cue );
                    } break;
                }
                free( psz );
            }

            webvtt_region_t *p_region = webvtt_region_GetByID( p_sys,
                                                               p_cue->settings.psz_region );
            if( p_region )
            {
                webvtt_region_AddCue( p_region, p_cue );
                assert( p_region->p_child );
            }
            else
            {
                webvtt_domnode_AppendLast( &p_sys->p_root->p_child, p_cue );
                p_cue->p_parent = (webvtt_dom_node_t *) p_sys->p_root;
            }
        }
    }
    return 0;
}