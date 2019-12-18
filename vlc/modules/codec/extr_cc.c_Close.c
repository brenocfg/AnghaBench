#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_queue; int /*<<< orphan*/  p_dtvcc; scalar_t__ p_cea708; struct TYPE_5__* p_eia608; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEA708_DTVCC_Demuxer_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CEA708_Decoder_Release (scalar_t__) ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t *)p_this;
    decoder_sys_t *p_sys = p_dec->p_sys;

    free( p_sys->p_eia608 );
    if( p_sys->p_cea708 )
    {
        CEA708_Decoder_Release( p_sys->p_cea708 );
        CEA708_DTVCC_Demuxer_Release( p_sys->p_dtvcc );
    }

    block_ChainRelease( p_sys->p_queue );
    free( p_sys );
}