#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  m_current_tile_number; } ;
typedef  TYPE_1__ opj_j2k_t ;
typedef  int /*<<< orphan*/  OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  opj_j2k_compare_SQcd_SQcc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OPJ_BOOL opj_j2k_compare_qcc(opj_j2k_t *p_j2k,
                                    OPJ_UINT32 p_first_comp_no, OPJ_UINT32 p_second_comp_no)
{
    return opj_j2k_compare_SQcd_SQcc(p_j2k, p_j2k->m_current_tile_number,
                                     p_first_comp_no, p_second_comp_no);
}