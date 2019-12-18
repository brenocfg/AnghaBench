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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  h264_slice_t ;
typedef  int /*<<< orphan*/  h264_sequence_parameter_set_t ;

/* Variables and functions */
 int h264_infer_pic_struct (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int,int) ; 

uint8_t h264_get_num_ts( const h264_sequence_parameter_set_t *p_sps,
                         const h264_slice_t *p_slice, uint8_t i_pic_struct,
                         int tFOC, int bFOC )
{
    i_pic_struct = h264_infer_pic_struct( p_sps, p_slice, i_pic_struct, tFOC, bFOC );
    /* !WARN modified with nuit field based multiplier for values 0, 7 and 8 */
    const uint8_t rgi_numclock[9] = { 2, 1, 1, 2, 2, 3, 3, 4, 6 };
    return rgi_numclock[ i_pic_struct ];
}