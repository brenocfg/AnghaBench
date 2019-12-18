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
struct hxxx_bsfw_ep3b_ctx_s {int dummy; } ;
struct hevc_dcr_values {void** general_configuration; int /*<<< orphan*/  b_temporalIdNested; void* i_numTemporalLayer; } ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 int /*<<< orphan*/  bs_init_custom (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,struct hxxx_bsfw_ep3b_ctx_s*) ; 
 void* bs_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bs_read1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hxxx_bsfw_ep3b_callbacks ; 
 int /*<<< orphan*/  hxxx_bsfw_ep3b_ctx_init (struct hxxx_bsfw_ep3b_ctx_s*) ; 

__attribute__((used)) static void hevc_dcr_params_from_vps( const uint8_t * p_buffer, size_t i_buffer,
                                      struct hevc_dcr_values *p_values )
{
    if( i_buffer < 19 )
        return;

    bs_t bs;
    struct hxxx_bsfw_ep3b_ctx_s bsctx;
    hxxx_bsfw_ep3b_ctx_init( &bsctx );
    bs_init_custom( &bs, p_buffer, i_buffer, &hxxx_bsfw_ep3b_callbacks, &bsctx );

    /* first two bytes are the NAL header, 3rd and 4th are:
        vps_video_parameter_set_id(4)
        vps_reserved_3_2bis(2)
        vps_max_layers_minus1(6)
        vps_max_sub_layers_minus1(3)
        vps_temporal_id_nesting_flags
    */
    bs_skip( &bs, 16 + 4 + 2 + 6 );
    p_values->i_numTemporalLayer = bs_read( &bs, 3 ) + 1;
    p_values->b_temporalIdNested = bs_read1( &bs );

    /* 5th & 6th are reserved 0xffff */
    bs_skip( &bs, 16 );
    /* copy the first 12 bytes of profile tier */
    for( unsigned i=0; i<12; i++ )
        p_values->general_configuration[i] = bs_read( &bs, 8 );
}