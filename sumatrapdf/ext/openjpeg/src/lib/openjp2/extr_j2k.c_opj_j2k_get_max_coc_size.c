#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ tw; scalar_t__ th; } ;
struct TYPE_8__ {TYPE_2__* m_private_image; TYPE_1__ m_cp; } ;
typedef  TYPE_3__ opj_j2k_t ;
struct TYPE_7__ {scalar_t__ numcomps; } ;
typedef  scalar_t__ OPJ_UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  opj_j2k_get_SPCod_SPCoc_size (TYPE_3__*,scalar_t__,scalar_t__) ; 
 scalar_t__ opj_uint_max (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OPJ_UINT32 opj_j2k_get_max_coc_size(opj_j2k_t *p_j2k)
{
    OPJ_UINT32 i, j;
    OPJ_UINT32 l_nb_comp;
    OPJ_UINT32 l_nb_tiles;
    OPJ_UINT32 l_max = 0;

    /* preconditions */

    l_nb_tiles = p_j2k->m_cp.tw * p_j2k->m_cp.th ;
    l_nb_comp = p_j2k->m_private_image->numcomps;

    for (i = 0; i < l_nb_tiles; ++i) {
        for (j = 0; j < l_nb_comp; ++j) {
            l_max = opj_uint_max(l_max, opj_j2k_get_SPCod_SPCoc_size(p_j2k, i, j));
        }
    }

    return 6 + l_max;
}