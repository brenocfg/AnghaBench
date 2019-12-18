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
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_5__ {scalar_t__ i_queue; int /*<<< orphan*/ * p_queue; int /*<<< orphan*/  p_cea708; int /*<<< orphan*/  p_dtvcc; scalar_t__ p_eia608; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEA708_DTVCC_Demuxer_Flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CEA708_Decoder_Flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Eia608Init (scalar_t__) ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Flush( decoder_t *p_dec )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    if( p_sys->p_eia608 )
    {
        Eia608Init( p_sys->p_eia608 );
    }
    else
    {
        CEA708_DTVCC_Demuxer_Flush( p_sys->p_dtvcc );
        CEA708_Decoder_Flush( p_sys->p_cea708 );
    }

    block_ChainRelease( p_sys->p_queue );
    p_sys->p_queue = NULL;
    p_sys->i_queue = 0;
}