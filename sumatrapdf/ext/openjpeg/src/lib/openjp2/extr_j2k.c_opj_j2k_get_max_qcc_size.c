#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  opj_j2k_t ;
typedef  int /*<<< orphan*/  OPJ_UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  opj_j2k_get_max_coc_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static OPJ_UINT32 opj_j2k_get_max_qcc_size(opj_j2k_t *p_j2k)
{
    return opj_j2k_get_max_coc_size(p_j2k);
}