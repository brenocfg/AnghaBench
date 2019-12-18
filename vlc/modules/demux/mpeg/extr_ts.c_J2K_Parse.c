#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_5__ {int i_buffer; int /*<<< orphan*/ * p_buffer; int /*<<< orphan*/  i_length; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 scalar_t__ GetWBE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_tick_from_samples (scalar_t__,scalar_t__) ; 

__attribute__((used)) static block_t *J2K_Parse( demux_t *p_demux, block_t *p_block, bool b_interlaced )
{
    const uint8_t *p_buf = p_block->p_buffer;

    if( p_block->i_buffer < ((b_interlaced) ? 48 : 38) )
        goto invalid;

    if( memcmp( p_buf, "elsmfrat", 8 ) )
        goto invalid;

    uint16_t i_den = GetWBE( &p_buf[8] );
    uint16_t i_num = GetWBE( &p_buf[10] );
    if( i_den == 0 )
        goto invalid;
    p_block->i_length = vlc_tick_from_samples( i_den, i_num );

    p_block->p_buffer += (b_interlaced) ? 48 : 38;
    p_block->i_buffer -= (b_interlaced) ? 48 : 38;

    return p_block;

invalid:
    msg_Warn( p_demux, "invalid J2K header, dropping codestream" );
    block_Release( p_block );
    return NULL;
}