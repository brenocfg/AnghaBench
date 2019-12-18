#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_5__ {scalar_t__ p_sps_pps_buf; int /*<<< orphan*/  i_nal_size; scalar_t__ i_sps_pps_size; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ h264_avcC_to_AnnexB_NAL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crystal_insert_sps_pps( decoder_t *p_dec,
                                   uint8_t *p_buf,
                                   uint32_t i_buf_size)
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    p_sys->i_sps_pps_size = 0;
    p_sys->p_sps_pps_buf = h264_avcC_to_AnnexB_NAL( p_buf, i_buf_size,
                           &p_sys->i_sps_pps_size, &p_sys->i_nal_size );

    return (p_sys->p_sps_pps_buf) ? VLC_SUCCESS : VLC_EGENERIC;
}