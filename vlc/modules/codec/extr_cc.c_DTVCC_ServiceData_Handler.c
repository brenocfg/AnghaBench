#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int uint8_t ;
struct TYPE_3__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_cea708; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEA708_Decoder_Push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,size_t) ; 

__attribute__((used)) static void DTVCC_ServiceData_Handler( void *priv, uint8_t i_sid, vlc_tick_t i_time,
                                       const uint8_t *p_data, size_t i_data )
{
    decoder_t *p_dec = priv;
    decoder_sys_t *p_sys = p_dec->p_sys;
    //msg_Err( p_dec, "DTVCC_ServiceData_Handler sid %d bytes %ld", i_sid, i_data );
    if( i_sid == 1 )
        CEA708_Decoder_Push( p_sys->p_cea708, i_time, p_data, i_data );
}