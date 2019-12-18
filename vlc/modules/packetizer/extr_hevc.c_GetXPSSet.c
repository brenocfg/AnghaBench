#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  hevc_video_parameter_set_t ;
typedef  int /*<<< orphan*/  hevc_sequence_parameter_set_t ;
typedef  int /*<<< orphan*/  hevc_picture_parameter_set_t ;
struct TYPE_8__ {TYPE_1__* rg_vps; TYPE_3__* rg_sps; TYPE_2__* rg_pps; } ;
typedef  TYPE_4__ decoder_sys_t ;
struct TYPE_7__ {int /*<<< orphan*/ * p_decoded; } ;
struct TYPE_6__ {int /*<<< orphan*/ * p_decoded; } ;
struct TYPE_5__ {int /*<<< orphan*/ * p_decoded; } ;

/* Variables and functions */
 size_t hevc_get_pps_sps_id (int /*<<< orphan*/ *) ; 
 size_t hevc_get_sps_vps_id (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void GetXPSSet(uint8_t i_pps_id, void *priv,
                      hevc_picture_parameter_set_t **pp_pps,
                      hevc_sequence_parameter_set_t **pp_sps,
                      hevc_video_parameter_set_t **pp_vps)
{
    decoder_sys_t *p_sys = priv;
    *pp_sps = NULL;
    *pp_vps = NULL;
    if((*pp_pps = p_sys->rg_pps[i_pps_id].p_decoded))
        if((*pp_sps = p_sys->rg_sps[hevc_get_pps_sps_id(*pp_pps)].p_decoded))
            *pp_vps = p_sys->rg_vps[hevc_get_sps_vps_id(*pp_sps)].p_decoded;
}