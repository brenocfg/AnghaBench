#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_4__* cp; } ;
typedef  TYPE_3__ opj_tcd_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_11__ {scalar_t__ m_fixed_quality; scalar_t__ m_disto_alloc; } ;
struct TYPE_12__ {TYPE_1__ m_enc; } ;
struct TYPE_14__ {TYPE_2__ m_specific_param; } ;
typedef  TYPE_4__ opj_cp_t ;
struct TYPE_15__ {scalar_t__ index_write; } ;
typedef  TYPE_5__ opj_codestream_info_t ;
typedef  int /*<<< orphan*/  OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_tcd_rateallocate (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_tcd_rateallocate_fixed (TYPE_3__*) ; 

__attribute__((used)) static OPJ_BOOL opj_tcd_rate_allocate_encode(opj_tcd_t *p_tcd,
        OPJ_BYTE * p_dest_data,
        OPJ_UINT32 p_max_dest_size,
        opj_codestream_info_t *p_cstr_info,
        opj_event_mgr_t *p_manager)
{
    opj_cp_t * l_cp = p_tcd->cp;
    OPJ_UINT32 l_nb_written = 0;

    if (p_cstr_info)  {
        p_cstr_info->index_write = 0;
    }

    if (l_cp->m_specific_param.m_enc.m_disto_alloc ||
            l_cp->m_specific_param.m_enc.m_fixed_quality)  {
        /* fixed_quality */
        /* Normal Rate/distortion allocation */
        if (! opj_tcd_rateallocate(p_tcd, p_dest_data, &l_nb_written, p_max_dest_size,
                                   p_cstr_info, p_manager)) {
            return OPJ_FALSE;
        }
    } else {
        /* Fixed layer allocation */
        opj_tcd_rateallocate_fixed(p_tcd);
    }

    return OPJ_TRUE;
}