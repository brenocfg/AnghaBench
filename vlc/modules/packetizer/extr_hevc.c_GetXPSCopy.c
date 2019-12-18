#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hevc_tuple_s {scalar_t__ p_nal; } ;
struct TYPE_3__ {struct hevc_tuple_s* rg_pps; struct hevc_tuple_s* rg_sps; struct hevc_tuple_s* rg_vps; } ;
typedef  TYPE_1__ decoder_sys_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 size_t HEVC_PPS_ID_MAX ; 
 size_t HEVC_SPS_ID_MAX ; 
 size_t HEVC_VPS_ID_MAX ; 
 int /*<<< orphan*/  block_ChainLastAppend (int /*<<< orphan*/ ***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * block_Duplicate (scalar_t__) ; 

__attribute__((used)) static block_t *GetXPSCopy(decoder_sys_t *p_sys)
{
    block_t *p_chain = NULL;
    block_t **pp_append = &p_chain;
    struct hevc_tuple_s *xpstype[3] = {p_sys->rg_vps, p_sys->rg_sps, p_sys->rg_pps};
    size_t xpsmax[3] = {HEVC_VPS_ID_MAX, HEVC_SPS_ID_MAX, HEVC_PPS_ID_MAX};
    for(size_t i=0; i<3; i++)
        for(size_t j=0; j<xpsmax[i]; j++)
        {
            block_t *p_dup;
            if(xpstype[i]->p_nal &&
               (p_dup = block_Duplicate(xpstype[i]->p_nal)))
                block_ChainLastAppend(&pp_append, p_dup);
        };
    return p_chain;
}