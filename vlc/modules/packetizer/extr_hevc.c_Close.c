#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_16__ {TYPE_8__* p_sys; } ;
typedef  TYPE_7__ decoder_t ;
struct TYPE_12__ {int /*<<< orphan*/  p_chain; } ;
struct TYPE_11__ {int /*<<< orphan*/  p_chain; } ;
struct TYPE_10__ {int /*<<< orphan*/  p_chain; } ;
struct TYPE_17__ {int /*<<< orphan*/  p_ccs; int /*<<< orphan*/  p_timing; TYPE_6__* rg_vps; TYPE_5__* rg_sps; TYPE_4__* rg_pps; TYPE_3__ post; TYPE_2__ pre; TYPE_1__ frame; int /*<<< orphan*/  packetizer; } ;
typedef  TYPE_8__ decoder_sys_t ;
struct TYPE_15__ {scalar_t__ p_nal; scalar_t__ p_decoded; } ;
struct TYPE_14__ {scalar_t__ p_nal; scalar_t__ p_decoded; } ;
struct TYPE_13__ {scalar_t__ p_nal; scalar_t__ p_decoded; } ;

/* Variables and functions */
 unsigned int HEVC_PPS_ID_MAX ; 
 unsigned int HEVC_SPS_ID_MAX ; 
 unsigned int HEVC_VPS_ID_MAX ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (scalar_t__) ; 
 int /*<<< orphan*/  cc_storage_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_8__*) ; 
 int /*<<< orphan*/  hevc_rbsp_release_pps (scalar_t__) ; 
 int /*<<< orphan*/  hevc_rbsp_release_sps (scalar_t__) ; 
 int /*<<< orphan*/  hevc_rbsp_release_vps (scalar_t__) ; 
 int /*<<< orphan*/  hevc_release_sei_pic_timing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packetizer_Clean (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close(vlc_object_t *p_this)
{
    decoder_t *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys = p_dec->p_sys;
    packetizer_Clean(&p_sys->packetizer);

    block_ChainRelease(p_sys->frame.p_chain);
    block_ChainRelease(p_sys->pre.p_chain);
    block_ChainRelease(p_sys->post.p_chain);

    for(unsigned i=0;i<=HEVC_PPS_ID_MAX; i++)
    {
        if(p_sys->rg_pps[i].p_decoded)
            hevc_rbsp_release_pps(p_sys->rg_pps[i].p_decoded);
        if(p_sys->rg_pps[i].p_nal)
            block_Release(p_sys->rg_pps[i].p_nal);
    }

    for(unsigned i=0;i<=HEVC_SPS_ID_MAX; i++)
    {
        if(p_sys->rg_sps[i].p_decoded)
            hevc_rbsp_release_sps(p_sys->rg_sps[i].p_decoded);
        if(p_sys->rg_sps[i].p_nal)
            block_Release(p_sys->rg_sps[i].p_nal);
    }

    for(unsigned i=0;i<=HEVC_VPS_ID_MAX; i++)
    {
        if(p_sys->rg_vps[i].p_decoded)
            hevc_rbsp_release_vps(p_sys->rg_vps[i].p_decoded);
        if(p_sys->rg_vps[i].p_nal)
            block_Release(p_sys->rg_vps[i].p_nal);
    }

    hevc_release_sei_pic_timing( p_sys->p_timing );

    cc_storage_delete( p_sys->p_ccs );

    free(p_sys);
}