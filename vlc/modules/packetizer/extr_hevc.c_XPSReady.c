#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  hevc_sequence_parameter_set_t ;
typedef  int /*<<< orphan*/  hevc_picture_parameter_set_t ;
struct TYPE_9__ {TYPE_1__* rg_vps; TYPE_3__* rg_sps; TYPE_2__* rg_pps; } ;
typedef  TYPE_4__ decoder_sys_t ;
struct TYPE_8__ {int /*<<< orphan*/ * p_decoded; } ;
struct TYPE_7__ {int /*<<< orphan*/ * p_decoded; } ;
struct TYPE_6__ {scalar_t__ p_decoded; } ;

/* Variables and functions */
 unsigned int HEVC_PPS_ID_MAX ; 
 size_t hevc_get_pps_sps_id (int /*<<< orphan*/  const*) ; 
 size_t hevc_get_sps_vps_id (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool XPSReady(decoder_sys_t *p_sys)
{
    for(unsigned i=0;i<=HEVC_PPS_ID_MAX; i++)
    {
        const hevc_picture_parameter_set_t *p_pps = p_sys->rg_pps[i].p_decoded;
        if (p_pps)
        {
            uint8_t id_sps = hevc_get_pps_sps_id(p_pps);
            const hevc_sequence_parameter_set_t *p_sps = p_sys->rg_sps[id_sps].p_decoded;
            if(p_sps)
            {
                uint8_t id_vps = hevc_get_sps_vps_id(p_sps);
                if(p_sys->rg_vps[id_vps].p_decoded)
                    return true;
            }
        }
    }
    return false;
}