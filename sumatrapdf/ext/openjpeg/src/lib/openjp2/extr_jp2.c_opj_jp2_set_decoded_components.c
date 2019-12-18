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
struct TYPE_3__ {int /*<<< orphan*/  j2k; } ;
typedef  TYPE_1__ opj_jp2_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  int /*<<< orphan*/  OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  opj_j2k_set_decoded_components (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

OPJ_BOOL opj_jp2_set_decoded_components(opj_jp2_t *p_jp2,
                                        OPJ_UINT32 numcomps,
                                        const OPJ_UINT32* comps_indices,
                                        opj_event_mgr_t * p_manager)
{
    return opj_j2k_set_decoded_components(p_jp2->j2k,
                                          numcomps, comps_indices,
                                          p_manager);
}