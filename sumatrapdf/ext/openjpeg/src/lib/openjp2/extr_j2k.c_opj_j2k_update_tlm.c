#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ m_tlm_sot_offsets_current; } ;
struct TYPE_6__ {TYPE_1__ m_encoder; } ;
struct TYPE_7__ {TYPE_2__ m_specific_param; int /*<<< orphan*/  m_current_tile_number; } ;
typedef  TYPE_3__ opj_j2k_t ;
typedef  int /*<<< orphan*/  OPJ_UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  opj_write_bytes (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void opj_j2k_update_tlm(opj_j2k_t * p_j2k, OPJ_UINT32 p_tile_part_size)
{
    opj_write_bytes(p_j2k->m_specific_param.m_encoder.m_tlm_sot_offsets_current,
                    p_j2k->m_current_tile_number, 1);           /* PSOT */
    ++p_j2k->m_specific_param.m_encoder.m_tlm_sot_offsets_current;

    opj_write_bytes(p_j2k->m_specific_param.m_encoder.m_tlm_sot_offsets_current,
                    p_tile_part_size, 4);                                       /* PSOT */
    p_j2k->m_specific_param.m_encoder.m_tlm_sot_offsets_current += 4;
}