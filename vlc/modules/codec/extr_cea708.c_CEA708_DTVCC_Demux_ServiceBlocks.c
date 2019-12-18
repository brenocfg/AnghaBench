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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  priv; int /*<<< orphan*/  (* p_callback ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int const*,int const) ;} ;
typedef  TYPE_1__ cea708_demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int const*,int const) ; 

__attribute__((used)) static void CEA708_DTVCC_Demux_ServiceBlocks( cea708_demux_t *h, vlc_tick_t i_start,
                                              const uint8_t *p_data, size_t i_data )
{
    while( i_data >= 2 )
    {
        uint8_t i_sid = p_data[0] >> 5;
        const uint8_t i_block_size = p_data[0] & 0x1F;

        if( i_block_size == 0 || i_block_size > i_data - 1 )
        {
            return;
        }
        else if( i_sid == 0x07 )
        {
            i_sid = p_data[1] & 0x3F;
            if( i_sid < 0x07 )
                return;
            p_data += 1; i_data -= 1;
        }
        p_data += 1; i_data -= 1;

        h->p_callback( h->priv, i_sid, i_start, p_data, i_block_size );

        p_data += i_block_size;
        i_data -= i_block_size;
    }
}