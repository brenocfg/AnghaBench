#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_7__ {int i_wanted_page; int* i_page; int /*<<< orphan*/ * b_is_subtitle; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int DecodePacketX1_X23 (TYPE_1__*,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ) ; 
 int DecodePacketX25 (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static bool DecodeNormalPacket( decoder_t *p_dec, const uint8_t *packet,
                                int magazine, int row, vlc_tick_t pts )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    if( (p_sys->i_wanted_page != -1 &&
         p_sys->i_page[magazine] != p_sys->i_wanted_page)
         || !p_sys->b_is_subtitle[magazine] )
        return false;

    if( row < 24 ) /* row 1-23 : normal lines */
        return DecodePacketX1_X23( p_dec, packet, magazine, row, pts );
    else if( row == 25 ) /* row 25 : alternate header line */
        return DecodePacketX25( p_dec, packet, magazine );
    else
        return false;
}