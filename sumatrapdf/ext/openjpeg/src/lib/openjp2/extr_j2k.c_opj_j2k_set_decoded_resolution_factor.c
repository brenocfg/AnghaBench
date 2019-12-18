#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_5__* m_default_tcp; } ;
struct TYPE_19__ {TYPE_6__ m_decoder; } ;
struct TYPE_13__ {size_t m_reduce; } ;
struct TYPE_14__ {TYPE_1__ m_dec; } ;
struct TYPE_15__ {TYPE_2__ m_specific_param; } ;
struct TYPE_12__ {TYPE_9__* m_private_image; TYPE_7__ m_specific_param; TYPE_3__ m_cp; } ;
typedef  TYPE_10__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_21__ {size_t numcomps; TYPE_8__* comps; } ;
struct TYPE_20__ {size_t factor; } ;
struct TYPE_17__ {TYPE_4__* tccps; } ;
struct TYPE_16__ {size_t numresolutions; } ;
typedef  size_t OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

OPJ_BOOL opj_j2k_set_decoded_resolution_factor(opj_j2k_t *p_j2k,
        OPJ_UINT32 res_factor,
        opj_event_mgr_t * p_manager)
{
    OPJ_UINT32 it_comp;

    p_j2k->m_cp.m_specific_param.m_dec.m_reduce = res_factor;

    if (p_j2k->m_private_image) {
        if (p_j2k->m_private_image->comps) {
            if (p_j2k->m_specific_param.m_decoder.m_default_tcp) {
                if (p_j2k->m_specific_param.m_decoder.m_default_tcp->tccps) {
                    for (it_comp = 0 ; it_comp < p_j2k->m_private_image->numcomps; it_comp++) {
                        OPJ_UINT32 max_res =
                            p_j2k->m_specific_param.m_decoder.m_default_tcp->tccps[it_comp].numresolutions;
                        if (res_factor >= max_res) {
                            opj_event_msg(p_manager, EVT_ERROR,
                                          "Resolution factor is greater than the maximum resolution in the component.\n");
                            return OPJ_FALSE;
                        }
                        p_j2k->m_private_image->comps[it_comp].factor = res_factor;
                    }
                    return OPJ_TRUE;
                }
            }
        }
    }

    return OPJ_FALSE;
}