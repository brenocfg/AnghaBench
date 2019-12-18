#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_pic_parameter_set_id; } ;
typedef  TYPE_1__ h264_slice_t ;
typedef  int /*<<< orphan*/  h264_sequence_parameter_set_t ;
typedef  int /*<<< orphan*/  h264_picture_parameter_set_t ;
struct TYPE_10__ {int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_2__ decoder_t ;
typedef  int /*<<< orphan*/  decoder_sys_t ;
struct TYPE_11__ {size_t i_buffer; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  ActivateSets (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  GetSPSPPS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  h264_decode_slice (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**),int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  hxxx_strip_AnnexB_startcode (int /*<<< orphan*/  const**,size_t*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool ParseSliceHeader( decoder_t *p_dec, const block_t *p_frag, h264_slice_t *p_slice )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    const uint8_t *p_stripped = p_frag->p_buffer;
    size_t i_stripped = p_frag->i_buffer;

    if( !hxxx_strip_AnnexB_startcode( &p_stripped, &i_stripped ) || i_stripped < 2 )
        return false;

    if( !h264_decode_slice( p_stripped, i_stripped, GetSPSPPS, p_sys, p_slice ) )
        return false;

    const h264_sequence_parameter_set_t *p_sps;
    const h264_picture_parameter_set_t *p_pps;
    GetSPSPPS( p_slice->i_pic_parameter_set_id, p_sys, &p_sps, &p_pps );
    if( unlikely( !p_sps || !p_pps) )
        return false;

    ActivateSets( p_dec, p_sps, p_pps );

    return true;
}