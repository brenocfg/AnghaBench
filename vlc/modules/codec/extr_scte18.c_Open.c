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
struct TYPE_7__ {scalar_t__ i_codec; } ;
struct TYPE_8__ {scalar_t__ i_codec; } ;
struct TYPE_9__ {TYPE_1__ fmt_out; int /*<<< orphan*/  pf_decode; TYPE_4__* p_sys; TYPE_2__ fmt_in; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_10__ {int /*<<< orphan*/  p_handle; } ;
typedef  TYPE_4__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Decode ; 
 scalar_t__ VLC_CODEC_SCTE_18 ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  atsc_a65_handle_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_4__* malloc (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int Open( vlc_object_t *object )
{
    decoder_t *dec = (decoder_t *)object;

    if ( dec->fmt_in.i_codec != VLC_CODEC_SCTE_18 )
        return VLC_EGENERIC;

    decoder_sys_t *p_sys = malloc( sizeof(decoder_sys_t) );
    if( unlikely(!p_sys) )
        return VLC_ENOMEM;

    p_sys->p_handle = atsc_a65_handle_New( NULL );
    if( !p_sys->p_handle )
    {
        free( p_sys );
        return VLC_EGENERIC;
    }

    dec->p_sys = p_sys;
    dec->pf_decode = Decode;
    dec->fmt_out.i_codec = 0;

    return VLC_SUCCESS;
}