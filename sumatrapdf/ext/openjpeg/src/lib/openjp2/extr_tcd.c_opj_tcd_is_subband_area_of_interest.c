#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {size_t numresolutions; scalar_t__ y1; scalar_t__ x1; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_6__ opj_tcd_tilecomp_t ;
struct TYPE_16__ {int /*<<< orphan*/  win_y1; int /*<<< orphan*/  win_x1; int /*<<< orphan*/  win_y0; int /*<<< orphan*/  win_x0; TYPE_5__* image; TYPE_4__* tcd_image; TYPE_2__* tcp; } ;
typedef  TYPE_7__ opj_tcd_t ;
struct TYPE_17__ {int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
typedef  TYPE_8__ opj_image_comp_t ;
struct TYPE_14__ {TYPE_8__* comps; } ;
struct TYPE_13__ {TYPE_3__* tiles; } ;
struct TYPE_12__ {TYPE_6__* comps; } ;
struct TYPE_11__ {TYPE_1__* tccps; } ;
struct TYPE_10__ {int qmfbid; } ;
typedef  size_t OPJ_UINT32 ;
typedef  int OPJ_BOOL ;

/* Variables and functions */
 size_t opj_uint_adds (size_t,size_t) ; 
 int /*<<< orphan*/  opj_uint_ceildiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t opj_uint_ceildivpow2 (size_t,size_t) ; 
 size_t opj_uint_max (size_t,int /*<<< orphan*/ ) ; 
 size_t opj_uint_min (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,int) ; 

OPJ_BOOL opj_tcd_is_subband_area_of_interest(opj_tcd_t *tcd,
        OPJ_UINT32 compno,
        OPJ_UINT32 resno,
        OPJ_UINT32 bandno,
        OPJ_UINT32 band_x0,
        OPJ_UINT32 band_y0,
        OPJ_UINT32 band_x1,
        OPJ_UINT32 band_y1)
{
    /* Note: those values for filter_margin are in part the result of */
    /* experimentation. The value 2 for QMFBID=1 (5x3 filter) can be linked */
    /* to the maximum left/right extension given in tables F.2 and F.3 of the */
    /* standard. The value 3 for QMFBID=0 (9x7 filter) is more suspicious, */
    /* since F.2 and F.3 would lead to 4 instead, so the current 3 might be */
    /* needed to be bumped to 4, in case inconsistencies are found while */
    /* decoding parts of irreversible coded images. */
    /* See opj_dwt_decode_partial_53 and opj_dwt_decode_partial_97 as well */
    OPJ_UINT32 filter_margin = (tcd->tcp->tccps[compno].qmfbid == 1) ? 2 : 3;
    opj_tcd_tilecomp_t *tilec = &(tcd->tcd_image->tiles->comps[compno]);
    opj_image_comp_t* image_comp = &(tcd->image->comps[compno]);
    /* Compute the intersection of the area of interest, expressed in tile coordinates */
    /* with the tile coordinates */
    OPJ_UINT32 tcx0 = opj_uint_max(
                          (OPJ_UINT32)tilec->x0,
                          opj_uint_ceildiv(tcd->win_x0, image_comp->dx));
    OPJ_UINT32 tcy0 = opj_uint_max(
                          (OPJ_UINT32)tilec->y0,
                          opj_uint_ceildiv(tcd->win_y0, image_comp->dy));
    OPJ_UINT32 tcx1 = opj_uint_min(
                          (OPJ_UINT32)tilec->x1,
                          opj_uint_ceildiv(tcd->win_x1, image_comp->dx));
    OPJ_UINT32 tcy1 = opj_uint_min(
                          (OPJ_UINT32)tilec->y1,
                          opj_uint_ceildiv(tcd->win_y1, image_comp->dy));
    /* Compute number of decomposition for this band. See table F-1 */
    OPJ_UINT32 nb = (resno == 0) ?
                    tilec->numresolutions - 1 :
                    tilec->numresolutions - resno;
    /* Map above tile-based coordinates to sub-band-based coordinates per */
    /* equation B-15 of the standard */
    OPJ_UINT32 x0b = bandno & 1;
    OPJ_UINT32 y0b = bandno >> 1;
    OPJ_UINT32 tbx0 = (nb == 0) ? tcx0 :
                      (tcx0 <= (1U << (nb - 1)) * x0b) ? 0 :
                      opj_uint_ceildivpow2(tcx0 - (1U << (nb - 1)) * x0b, nb);
    OPJ_UINT32 tby0 = (nb == 0) ? tcy0 :
                      (tcy0 <= (1U << (nb - 1)) * y0b) ? 0 :
                      opj_uint_ceildivpow2(tcy0 - (1U << (nb - 1)) * y0b, nb);
    OPJ_UINT32 tbx1 = (nb == 0) ? tcx1 :
                      (tcx1 <= (1U << (nb - 1)) * x0b) ? 0 :
                      opj_uint_ceildivpow2(tcx1 - (1U << (nb - 1)) * x0b, nb);
    OPJ_UINT32 tby1 = (nb == 0) ? tcy1 :
                      (tcy1 <= (1U << (nb - 1)) * y0b) ? 0 :
                      opj_uint_ceildivpow2(tcy1 - (1U << (nb - 1)) * y0b, nb);
    OPJ_BOOL intersects;

    if (tbx0 < filter_margin) {
        tbx0 = 0;
    } else {
        tbx0 -= filter_margin;
    }
    if (tby0 < filter_margin) {
        tby0 = 0;
    } else {
        tby0 -= filter_margin;
    }
    tbx1 = opj_uint_adds(tbx1, filter_margin);
    tby1 = opj_uint_adds(tby1, filter_margin);

    intersects = band_x0 < tbx1 && band_y0 < tby1 && band_x1 > tbx0 &&
                 band_y1 > tby0;

#ifdef DEBUG_VERBOSE
    printf("compno=%u resno=%u nb=%u bandno=%u x0b=%u y0b=%u band=%u,%u,%u,%u tb=%u,%u,%u,%u -> %u\n",
           compno, resno, nb, bandno, x0b, y0b,
           band_x0, band_y0, band_x1, band_y1,
           tbx0, tby0, tbx1, tby1, intersects);
#endif
    return intersects;
}