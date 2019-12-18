#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_7__ {scalar_t__ p_ep; } ;
struct TYPE_6__ {scalar_t__ p_sh; } ;
struct TYPE_9__ {int /*<<< orphan*/  cc; int /*<<< orphan*/  cc_next; TYPE_2__ ep; TYPE_1__ sh; scalar_t__ p_frame; int /*<<< orphan*/  packetizer; } ;
typedef  TYPE_4__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_Release (scalar_t__) ; 
 int /*<<< orphan*/  cc_Exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  packetizer_Clean (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    decoder_t     *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys = p_dec->p_sys;

    packetizer_Clean( &p_sys->packetizer );
    if( p_sys->p_frame )
        block_Release( p_sys->p_frame );
    if( p_sys->sh.p_sh )
        block_Release( p_sys->sh.p_sh );
    if( p_sys->ep.p_ep )
        block_Release( p_sys->ep.p_ep );

    cc_Exit( &p_sys->cc_next );
    cc_Exit( &p_sys->cc );

    free( p_sys );
}