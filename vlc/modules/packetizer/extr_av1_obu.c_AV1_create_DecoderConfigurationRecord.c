#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  bs_t ;
struct TYPE_6__ {int high_bitdepth; int twelve_bit; int mono_chrome; int subsampling_x; int subsampling_y; int chroma_sample_position; } ;
struct TYPE_7__ {int seq_profile; TYPE_2__ color_config; TYPE_1__* operating_points; } ;
typedef  TYPE_3__ av1_OBU_sequence_header_t ;
struct TYPE_5__ {int seq_level_idx; int seq_tier; } ;

/* Variables and functions */
 int /*<<< orphan*/  bs_write (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  bs_write_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t const) ; 

size_t AV1_create_DecoderConfigurationRecord(uint8_t **pp_buffer,
                                             const av1_OBU_sequence_header_t *p_seq,
                                             size_t i_obu, const uint8_t *p_obus[],
                                             const size_t pi_obus[])
{
    size_t i_buffer = 4;
    for(size_t i=0; i<i_obu; i++)
        i_buffer += pi_obus[i];

    uint8_t *p_buffer = malloc(i_buffer);
    if(!p_buffer)
        return 0;

    bs_t bs;
    bs_write_init(&bs, p_buffer, i_buffer);
    bs_write(&bs, 1, 1); /* unsigned int (1) marker = 1; */
    bs_write(&bs, 7, 1); /* unsigned int (7) version = 1; */
    bs_write(&bs, 3, p_seq->seq_profile); /* unsigned int (3) seq_profile; */
    bs_write(&bs, 5, p_seq->operating_points[0].seq_level_idx); /* unsigned int (5) seq_level_idx_0; */

    bs_write(&bs, 1, p_seq->operating_points[0].seq_tier); /* unsigned int (1) seq_tier_0; */
    bs_write(&bs, 1, p_seq->color_config.high_bitdepth); /* unsigned int (1) high_bitdepth; */
    bs_write(&bs, 1, p_seq->color_config.twelve_bit); /* unsigned int (1) twelve_bit; */
    bs_write(&bs, 1, p_seq->color_config.mono_chrome); /* unsigned int (1) monochrome; */
    bs_write(&bs, 1, p_seq->color_config.subsampling_x); /* unsigned int (1) chroma_subsampling_x; */
    bs_write(&bs, 1, p_seq->color_config.subsampling_y); /* unsigned int (1) chroma_subsampling_y; */
    bs_write(&bs, 2, p_seq->color_config.chroma_sample_position); /* unsigned int (2) chroma_sample_position; */

    bs_write(&bs, 3, 0); /* unsigned int (3) reserved = 0; */
    bs_write(&bs, 1, 0); /* unsigned int (1) initial_presentation_delay_present; (can't compute it) */
    bs_write(&bs, 4, 0); /* unsigned int (4) reserved = 0; */

    /*unsigned int (8)[] configOBUs;*/
    size_t i_offset = 4;
    for(size_t i=0; i<i_obu; i++)
        memcpy(&p_buffer[i_offset], p_obus[i], pi_obus[i]);

    *pp_buffer = p_buffer;
    return i_buffer;
}