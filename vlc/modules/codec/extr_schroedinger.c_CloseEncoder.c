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
typedef  TYPE_1__ encoder_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_chain; scalar_t__ p_dts_fifo; struct TYPE_5__* p_format; scalar_t__ p_schro; } ;
typedef  TYPE_2__ encoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  schro_encoder_free (scalar_t__) ; 
 int /*<<< orphan*/  timestamp_FifoRelease (scalar_t__) ; 

__attribute__((used)) static void CloseEncoder( vlc_object_t *p_this )
{
    encoder_t *p_enc = (encoder_t *)p_this;
    encoder_sys_t *p_sys = p_enc->p_sys;

    /* Free the encoder resources */
    if( p_sys->p_schro )
        schro_encoder_free( p_sys->p_schro );

    free( p_sys->p_format );

    if( p_sys->p_dts_fifo )
        timestamp_FifoRelease( p_sys->p_dts_fifo );

    block_ChainRelease( p_sys->p_chain );

    free( p_sys );
}