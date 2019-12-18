#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_codec; } ;
struct TYPE_8__ {scalar_t__ i_codec; } ;
struct TYPE_9__ {int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_decode; TYPE_1__ fmt_out; TYPE_4__* p_sys; TYPE_2__ fmt_in; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_10__ {scalar_t__ i_frame_pts_delta; int /*<<< orphan*/  i_lastpts; int /*<<< orphan*/ * p_format; int /*<<< orphan*/ * p_schro; } ;
typedef  TYPE_4__ decoder_sys_t ;
typedef  int /*<<< orphan*/  SchroDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeBlock ; 
 int /*<<< orphan*/  Flush ; 
 scalar_t__ VLC_CODEC_DIRAC ; 
 int /*<<< orphan*/  VLC_CODEC_I420 ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_4__* malloc (int) ; 
 int /*<<< orphan*/ * schro_decoder_new () ; 
 int /*<<< orphan*/  schro_init () ; 

__attribute__((used)) static int OpenDecoder( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys;
    SchroDecoder *p_schro;

    if( p_dec->fmt_in.i_codec != VLC_CODEC_DIRAC )
    {
        return VLC_EGENERIC;
    }

    /* Allocate the memory needed to store the decoder's structure */
    p_sys = malloc(sizeof(decoder_sys_t));
    if( p_sys == NULL )
        return VLC_ENOMEM;

    /* Initialise the schroedinger (and hence liboil libraries */
    /* This does no allocation and is safe to call */
    schro_init();

    /* Initialise the schroedinger decoder */
    if( !(p_schro = schro_decoder_new()) )
    {
        free( p_sys );
        return VLC_EGENERIC;
    }

    p_dec->p_sys = p_sys;
    p_sys->p_schro = p_schro;
    p_sys->p_format = NULL;
    p_sys->i_lastpts = VLC_TICK_INVALID;
    p_sys->i_frame_pts_delta = 0;

    /* Set output properties */
    p_dec->fmt_out.i_codec = VLC_CODEC_I420;

    /* Set callbacks */
    p_dec->pf_decode = DecodeBlock;
    p_dec->pf_flush  = Flush;

    return VLC_SUCCESS;
}