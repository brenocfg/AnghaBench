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
typedef  int /*<<< orphan*/  sout_stream_t ;
struct TYPE_3__ {scalar_t__ psz_filters; } ;
typedef  TYPE_1__ sout_filters_config_t ;
typedef  int /*<<< orphan*/  audio_format_t ;
typedef  int /*<<< orphan*/  aout_filters_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_VAR_BOOL ; 
 int /*<<< orphan*/  VLC_VAR_STRING ; 
 int /*<<< orphan*/ * aout_FiltersNew (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_Destroy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static int transcode_audio_filters_init( sout_stream_t *p_stream,
                                         const sout_filters_config_t *p_cfg,
                                         const audio_format_t *p_dec_out,
                                         const audio_format_t *p_enc_in,
                                         aout_filters_t **pp_chain )
{
    /* Load user specified audio filters */
    /* XXX: These variable names come kinda out of nowhere... */
    var_Create( p_stream, "audio-time-stretch", VLC_VAR_BOOL );
    var_Create( p_stream, "audio-filter", VLC_VAR_STRING );
    if( p_cfg->psz_filters )
        var_SetString( p_stream, "audio-filter", p_cfg->psz_filters );
    *pp_chain = aout_FiltersNew( p_stream, p_dec_out, p_enc_in, NULL );
    var_Destroy( p_stream, "audio-filter" );
    var_Destroy( p_stream, "audio-time-stretch" );
    return ( *pp_chain != NULL ) ? VLC_SUCCESS : VLC_EGENERIC;
}