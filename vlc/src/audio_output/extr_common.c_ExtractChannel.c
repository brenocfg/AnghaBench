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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static inline void ExtractChannel( uint8_t *pi_dst, int i_dst_channels,
                                   const uint8_t *pi_src, int i_src_channels,
                                   int i_sample_count,
                                   const int *pi_selection, int i_bytes )
{
    for( int i = 0; i < i_sample_count; i++ )
    {
        for( int j = 0; j < i_dst_channels; j++ )
            memcpy( &pi_dst[j * i_bytes], &pi_src[pi_selection[j] * i_bytes], i_bytes );
        pi_dst += i_dst_channels * i_bytes;
        pi_src += i_src_channels * i_bytes;
    }
}