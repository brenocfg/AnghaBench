#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {scalar_t__ i_codec; } ;
struct TYPE_8__ {int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_decode; TYPE_3__* p_sys; TYPE_1__ fmt_in; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_9__ {int /*<<< orphan*/  pes; int /*<<< orphan*/  i_align; } ;
typedef  TYPE_3__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeBlock ; 
 int /*<<< orphan*/  DecodePESBlock ; 
 int /*<<< orphan*/  Flush ; 
 int /*<<< orphan*/  TTML_in_PES (TYPE_2__*) ; 
 scalar_t__ VLC_CODEC_TTML ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  ttml_in_pes_Init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_InheritInteger (TYPE_2__*,char*) ; 

int tt_OpenDecoder( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys;

    if( p_dec->fmt_in.i_codec != VLC_CODEC_TTML &&
        !TTML_in_PES(p_dec) )
        return VLC_EGENERIC;

    /* Allocate the memory needed to store the decoder's structure */
    p_dec->p_sys = p_sys = calloc( 1, sizeof( *p_sys ) );
    if( unlikely( p_sys == NULL ) )
        return VLC_ENOMEM;

    if( !TTML_in_PES( p_dec ) )
        p_dec->pf_decode = DecodeBlock;
    else
        p_dec->pf_decode = DecodePESBlock;
    p_dec->pf_flush = Flush;
    p_sys->i_align = var_InheritInteger( p_dec, "ttml-align" );
    ttml_in_pes_Init( &p_sys->pes );

    return VLC_SUCCESS;
}