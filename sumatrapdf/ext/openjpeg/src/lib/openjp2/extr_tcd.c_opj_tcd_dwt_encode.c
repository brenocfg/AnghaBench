#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_tcd_tilecomp_t ;
struct TYPE_9__ {scalar_t__ numcomps; int /*<<< orphan*/ * comps; } ;
typedef  TYPE_3__ opj_tcd_tile_t ;
struct TYPE_10__ {TYPE_2__* tcp; TYPE_1__* tcd_image; } ;
typedef  TYPE_4__ opj_tcd_t ;
struct TYPE_11__ {int qmfbid; } ;
typedef  TYPE_5__ opj_tccp_t ;
struct TYPE_8__ {TYPE_5__* tccps; } ;
struct TYPE_7__ {TYPE_3__* tiles; } ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_dwt_encode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_dwt_encode_real (int /*<<< orphan*/ *) ; 

__attribute__((used)) static OPJ_BOOL opj_tcd_dwt_encode(opj_tcd_t *p_tcd)
{
    opj_tcd_tile_t * l_tile = p_tcd->tcd_image->tiles;
    opj_tcd_tilecomp_t * l_tile_comp = p_tcd->tcd_image->tiles->comps;
    opj_tccp_t * l_tccp = p_tcd->tcp->tccps;
    OPJ_UINT32 compno;

    for (compno = 0; compno < l_tile->numcomps; ++compno) {
        if (l_tccp->qmfbid == 1) {
            if (! opj_dwt_encode(l_tile_comp)) {
                return OPJ_FALSE;
            }
        } else if (l_tccp->qmfbid == 0) {
            if (! opj_dwt_encode_real(l_tile_comp)) {
                return OPJ_FALSE;
            }
        }

        ++l_tile_comp;
        ++l_tccp;
    }

    return OPJ_TRUE;
}