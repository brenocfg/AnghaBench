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

/* Variables and functions */
 int /*<<< orphan*/  ExtractChannel (void*,int,void const*,int,int,int const*,int) ; 
 int /*<<< orphan*/  assert (int) ; 

void aout_ChannelExtract( void *p_dst, int i_dst_channels,
                          const void *p_src, int i_src_channels,
                          int i_sample_count, const int *pi_selection, int i_bits_per_sample )
{
    /* It does not work in place */
    assert( p_dst != p_src );

    /* Force the compiler to inline for the specific cases so it can optimize */
    if( i_bits_per_sample == 8 )
        ExtractChannel( p_dst, i_dst_channels, p_src, i_src_channels, i_sample_count, pi_selection, 1 );
    else  if( i_bits_per_sample == 16 )
        ExtractChannel( p_dst, i_dst_channels, p_src, i_src_channels, i_sample_count, pi_selection, 2 );
    else  if( i_bits_per_sample == 32 )
        ExtractChannel( p_dst, i_dst_channels, p_src, i_src_channels, i_sample_count, pi_selection, 4 );
    else  if( i_bits_per_sample == 64 )
        ExtractChannel( p_dst, i_dst_channels, p_src, i_src_channels, i_sample_count, pi_selection, 8 );
}