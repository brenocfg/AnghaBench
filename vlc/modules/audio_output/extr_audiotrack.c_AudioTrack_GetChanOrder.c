#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_CHAN_CENTER ; 
 int /*<<< orphan*/  AOUT_CHAN_LEFT ; 
 int /*<<< orphan*/  AOUT_CHAN_LFE ; 
 int AOUT_CHAN_MAX ; 
 int /*<<< orphan*/  AOUT_CHAN_MIDDLELEFT ; 
 int /*<<< orphan*/  AOUT_CHAN_MIDDLERIGHT ; 
 int /*<<< orphan*/  AOUT_CHAN_REARCENTER ; 
 int /*<<< orphan*/  AOUT_CHAN_REARLEFT ; 
 int /*<<< orphan*/  AOUT_CHAN_REARRIGHT ; 
 int /*<<< orphan*/  AOUT_CHAN_RIGHT ; 
 scalar_t__ HAS_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
AudioTrack_GetChanOrder( uint16_t i_physical_channels, uint32_t p_chans_out[] )
{
#define HAS_CHAN( x ) ( ( i_physical_channels & (x) ) == (x) )
    /* samples will be in the following order: FL FR FC LFE BL BR BC SL SR */
    int i = 0;

    if( HAS_CHAN( AOUT_CHAN_LEFT ) )
        p_chans_out[i++] = AOUT_CHAN_LEFT;
    if( HAS_CHAN( AOUT_CHAN_RIGHT ) )
        p_chans_out[i++] = AOUT_CHAN_RIGHT;

    if( HAS_CHAN( AOUT_CHAN_CENTER ) )
        p_chans_out[i++] = AOUT_CHAN_CENTER;

    if( HAS_CHAN( AOUT_CHAN_LFE ) )
        p_chans_out[i++] = AOUT_CHAN_LFE;

    if( HAS_CHAN( AOUT_CHAN_REARLEFT ) )
        p_chans_out[i++] = AOUT_CHAN_REARLEFT;
    if( HAS_CHAN( AOUT_CHAN_REARRIGHT ) )
        p_chans_out[i++] = AOUT_CHAN_REARRIGHT;

    if( HAS_CHAN( AOUT_CHAN_REARCENTER ) )
        p_chans_out[i++] = AOUT_CHAN_REARCENTER;

    if( HAS_CHAN( AOUT_CHAN_MIDDLELEFT ) )
        p_chans_out[i++] = AOUT_CHAN_MIDDLELEFT;
    if( HAS_CHAN( AOUT_CHAN_MIDDLERIGHT ) )
        p_chans_out[i++] = AOUT_CHAN_MIDDLERIGHT;

    assert( i <= AOUT_CHAN_MAX );
#undef HAS_CHAN
}