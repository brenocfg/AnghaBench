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
struct av1_operating_parameters_info_s {int /*<<< orphan*/  low_delay_mode_flag; void* encoder_buffer_delay; void* decoder_buffer_delay; } ;
typedef  scalar_t__ obu_u8_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 void* bs_read (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bs_read1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool av1_parse_operating_parameters_info(bs_t *p_bs,
                                                struct av1_operating_parameters_info_s *p_op,
                                                obu_u8_t buffer_delay_length_minus_1)
{
    p_op->decoder_buffer_delay = bs_read(p_bs, 1 + buffer_delay_length_minus_1);
    p_op->encoder_buffer_delay = bs_read(p_bs, 1 + buffer_delay_length_minus_1);
    p_op->low_delay_mode_flag = bs_read1(p_bs);
    return true;
}