#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int maxmarknum; int /*<<< orphan*/ * marker; scalar_t__ marknum; } ;
typedef  TYPE_3__ opj_tile_index_t ;
typedef  int /*<<< orphan*/  opj_marker_info_t ;
struct TYPE_6__ {int tw; int th; } ;
struct TYPE_9__ {TYPE_2__* cstr_index; TYPE_1__ m_cp; } ;
typedef  TYPE_4__ opj_j2k_t ;
struct TYPE_7__ {int nb_of_tiles; TYPE_3__* tile_index; } ;
typedef  size_t OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 scalar_t__ opj_calloc (int,int) ; 

__attribute__((used)) static OPJ_BOOL opj_j2k_allocate_tile_element_cstr_index(opj_j2k_t *p_j2k)
{
    OPJ_UINT32 it_tile = 0;

    p_j2k->cstr_index->nb_of_tiles = p_j2k->m_cp.tw * p_j2k->m_cp.th;
    p_j2k->cstr_index->tile_index = (opj_tile_index_t*)opj_calloc(
                                        p_j2k->cstr_index->nb_of_tiles, sizeof(opj_tile_index_t));
    if (!p_j2k->cstr_index->tile_index) {
        return OPJ_FALSE;
    }

    for (it_tile = 0; it_tile < p_j2k->cstr_index->nb_of_tiles; it_tile++) {
        p_j2k->cstr_index->tile_index[it_tile].maxmarknum = 100;
        p_j2k->cstr_index->tile_index[it_tile].marknum = 0;
        p_j2k->cstr_index->tile_index[it_tile].marker = (opj_marker_info_t*)
                opj_calloc(p_j2k->cstr_index->tile_index[it_tile].maxmarknum,
                           sizeof(opj_marker_info_t));
        if (!p_j2k->cstr_index->tile_index[it_tile].marker) {
            return OPJ_FALSE;
        }
    }

    return OPJ_TRUE;
}