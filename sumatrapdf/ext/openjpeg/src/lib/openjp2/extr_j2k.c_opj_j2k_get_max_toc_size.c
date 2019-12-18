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
struct TYPE_6__ {int /*<<< orphan*/  m_nb_tile_parts; } ;
typedef  TYPE_2__ opj_tcp_t ;
struct TYPE_5__ {int tw; int th; TYPE_2__* tcps; } ;
struct TYPE_7__ {TYPE_1__ m_cp; } ;
typedef  TYPE_3__ opj_j2k_t ;
typedef  int OPJ_UINT32 ;

/* Variables and functions */
 int opj_uint_max (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OPJ_UINT32 opj_j2k_get_max_toc_size(opj_j2k_t *p_j2k)
{
    OPJ_UINT32 i;
    OPJ_UINT32 l_nb_tiles;
    OPJ_UINT32 l_max = 0;
    opj_tcp_t * l_tcp = 00;

    l_tcp = p_j2k->m_cp.tcps;
    l_nb_tiles = p_j2k->m_cp.tw * p_j2k->m_cp.th ;

    for (i = 0; i < l_nb_tiles; ++i) {
        l_max = opj_uint_max(l_max, l_tcp->m_nb_tile_parts);

        ++l_tcp;
    }

    return 12 * l_max;
}