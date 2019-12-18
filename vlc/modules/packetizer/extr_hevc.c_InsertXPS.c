#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct hevc_tuple_s {void* p_decoded; TYPE_5__* p_nal; } ;
struct TYPE_10__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_11__ {int /*<<< orphan*/  p_active_pps; struct hevc_tuple_s* rg_pps; int /*<<< orphan*/  p_active_sps; struct hevc_tuple_s* rg_sps; int /*<<< orphan*/  p_active_vps; struct hevc_tuple_s* rg_vps; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_12__ {int* p_buffer; size_t i_buffer; } ;
typedef  TYPE_3__ block_t ;
struct TYPE_13__ {int* p_buffer; size_t i_buffer; } ;

/* Variables and functions */
#define  HEVC_NAL_PPS 130 
#define  HEVC_NAL_SPS 129 
#define  HEVC_NAL_VPS 128 
 int HEVC_PPS_ID_MAX ; 
 int HEVC_SPS_ID_MAX ; 
 int HEVC_VPS_ID_MAX ; 
 TYPE_5__* block_Duplicate (TYPE_3__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_5__*) ; 
 void* hevc_decode_pps (int const*,size_t,int) ; 
 void* hevc_decode_sps (int const*,size_t,int) ; 
 void* hevc_decode_vps (int const*,size_t,int) ; 
 int /*<<< orphan*/  hevc_rbsp_release_pps (void*) ; 
 int /*<<< orphan*/  hevc_rbsp_release_sps (void*) ; 
 int /*<<< orphan*/  hevc_rbsp_release_vps (void*) ; 
 scalar_t__ hxxx_strip_AnnexB_startcode (int const**,size_t*) ; 
 int /*<<< orphan*/  memcmp (int const*,int const*,size_t) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int) ; 

__attribute__((used)) static bool InsertXPS(decoder_t *p_dec, uint8_t i_nal_type, uint8_t i_id,
                      const block_t *p_nalb)
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    struct hevc_tuple_s *p_tuple;
    void **pp_active;

    switch(i_nal_type)
    {
        case HEVC_NAL_VPS:
            if(i_id > HEVC_VPS_ID_MAX)
                return false;
            p_tuple = &p_sys->rg_vps[i_id];
            pp_active = (void**)&p_sys->p_active_vps;
            break;
        case HEVC_NAL_SPS:
            if(i_id > HEVC_SPS_ID_MAX)
                return false;
            p_tuple = &p_sys->rg_sps[i_id];
            pp_active = (void**)&p_sys->p_active_sps;
            break;
        case HEVC_NAL_PPS:
            if(i_id > HEVC_PPS_ID_MAX)
                return false;
            p_tuple = &p_sys->rg_pps[i_id];
            pp_active = (void**)&p_sys->p_active_pps;
            break;
        default:
            return false;
    }

    /* Check if we really need to re-decode/replace */
    if(p_tuple->p_nal)
    {
        const uint8_t *p_stored = p_tuple->p_nal->p_buffer;
        size_t i_stored = p_tuple->p_nal->i_buffer;
        hxxx_strip_AnnexB_startcode(&p_stored, &i_stored);
        const uint8_t *p_new = p_nalb->p_buffer;
        size_t i_new = p_nalb->i_buffer;
        hxxx_strip_AnnexB_startcode(&p_new, &i_new);
        if(i_stored == i_new && !memcmp(p_stored, p_new, i_new))
            return true;
    }

    /* Free associated decoded version */
    if(p_tuple->p_decoded)
    {
        switch(i_nal_type)
        {
            case HEVC_NAL_VPS:
                hevc_rbsp_release_vps(p_tuple->p_decoded);
                break;
            case HEVC_NAL_SPS:
                hevc_rbsp_release_sps(p_tuple->p_decoded);
                break;
            case HEVC_NAL_PPS:
                hevc_rbsp_release_pps(p_tuple->p_decoded);
                break;
        }
        if(*pp_active == p_tuple->p_decoded)
            *pp_active = NULL;
        else
            pp_active = NULL; /* don't change pointer */
        p_tuple->p_decoded = NULL;
    }
    else pp_active = NULL;

    /* Free raw stored version */
    if(p_tuple->p_nal)
    {
        block_Release(p_tuple->p_nal);
        p_tuple->p_nal = NULL;
    }

    const uint8_t *p_buffer = p_nalb->p_buffer;
    size_t i_buffer = p_nalb->i_buffer;
    if( hxxx_strip_AnnexB_startcode( &p_buffer, &i_buffer ) )
    {
        /* Create decoded entries */
        switch(i_nal_type)
        {
            case HEVC_NAL_SPS:
                p_tuple->p_decoded = hevc_decode_sps(p_buffer, i_buffer, true);
                if(!p_tuple->p_decoded)
                {
                    msg_Err(p_dec, "Failed decoding SPS id %d", i_id);
                    return false;
                }
                break;
            case HEVC_NAL_PPS:
                p_tuple->p_decoded = hevc_decode_pps(p_buffer, i_buffer, true);
                if(!p_tuple->p_decoded)
                {
                    msg_Err(p_dec, "Failed decoding PPS id %d", i_id);
                    return false;
                }
                break;
            case HEVC_NAL_VPS:
                p_tuple->p_decoded = hevc_decode_vps(p_buffer, i_buffer, true);
                if(!p_tuple->p_decoded)
                {
                    msg_Err(p_dec, "Failed decoding VPS id %d", i_id);
                    return false;
                }
                break;
        }

        if(p_tuple->p_decoded && pp_active) /* restore active by id */
            *pp_active = p_tuple->p_decoded;

        p_tuple->p_nal = block_Duplicate((block_t *)p_nalb);

        return true;
    }

    return false;
}