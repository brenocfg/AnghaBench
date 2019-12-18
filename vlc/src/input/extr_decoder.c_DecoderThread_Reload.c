#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ i_cat; } ;
struct decoder_owner {int error; int /*<<< orphan*/  p_resource; int /*<<< orphan*/ * p_aout; TYPE_1__ fmt; int /*<<< orphan*/  dec; } ;
typedef  int /*<<< orphan*/  es_format_t ;
typedef  enum reload { ____Placeholder_reload } reload ;
typedef  int /*<<< orphan*/  decoder_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 scalar_t__ LoadDecoder (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int RELOAD_DECODER_AOUT ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  aout_DecDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  decoder_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 scalar_t__ es_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  input_resource_PutAout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DecoderThread_Reload( struct decoder_owner *p_owner, bool b_packetizer,
                                 const es_format_t *restrict p_fmt, enum reload reload )
{
    /* Copy p_fmt since it can be destroyed by decoder_Clean */
    decoder_t *p_dec = &p_owner->dec;
    es_format_t fmt_in;
    if( es_format_Copy( &fmt_in, p_fmt ) != VLC_SUCCESS )
    {
        p_owner->error = true;
        return VLC_EGENERIC;
    }

    /* Restart the decoder module */
    decoder_Clean( p_dec );
    p_owner->error = false;

    if( reload == RELOAD_DECODER_AOUT )
    {
        assert( p_owner->fmt.i_cat == AUDIO_ES );
        audio_output_t *p_aout = p_owner->p_aout;
        // no need to lock, the decoder and ModuleThread are dead
        p_owner->p_aout = NULL;
        if( p_aout )
        {
            aout_DecDelete( p_aout );
            input_resource_PutAout( p_owner->p_resource, p_aout );
        }
    }

    if( LoadDecoder( p_dec, b_packetizer, &fmt_in ) )
    {
        p_owner->error = true;
        es_format_Clean( &fmt_in );
        return VLC_EGENERIC;
    }
    es_format_Clean( &fmt_in );
    return VLC_SUCCESS;
}