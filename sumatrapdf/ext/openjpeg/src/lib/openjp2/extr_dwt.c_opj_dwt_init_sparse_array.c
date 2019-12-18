#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* resolutions; } ;
typedef  TYPE_2__ opj_tcd_tilecomp_t ;
struct TYPE_10__ {size_t numbands; size_t pw; size_t ph; scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; TYPE_6__* bands; } ;
typedef  TYPE_3__ opj_tcd_resolution_t ;
struct TYPE_8__ {TYPE_5__* dec; } ;
struct TYPE_11__ {size_t cw; size_t ch; TYPE_1__ cblks; } ;
typedef  TYPE_4__ opj_tcd_precinct_t ;
struct TYPE_12__ {int /*<<< orphan*/ * decoded_data; scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
typedef  TYPE_5__ opj_tcd_cblk_dec_t ;
struct TYPE_13__ {int bandno; scalar_t__ y0; scalar_t__ x0; TYPE_4__* precincts; } ;
typedef  TYPE_6__ opj_tcd_band_t ;
typedef  int /*<<< orphan*/  opj_sparse_array_int32_t ;
typedef  size_t OPJ_UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/ * opj_sparse_array_int32_create (size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_sparse_array_int32_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_sparse_array_int32_write (int /*<<< orphan*/ *,size_t,size_t,size_t,size_t,int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_uint_min (size_t,int) ; 

__attribute__((used)) static opj_sparse_array_int32_t* opj_dwt_init_sparse_array(
    opj_tcd_tilecomp_t* tilec,
    OPJ_UINT32 numres)
{
    opj_tcd_resolution_t* tr_max = &(tilec->resolutions[numres - 1]);
    OPJ_UINT32 w = (OPJ_UINT32)(tr_max->x1 - tr_max->x0);
    OPJ_UINT32 h = (OPJ_UINT32)(tr_max->y1 - tr_max->y0);
    OPJ_UINT32 resno, bandno, precno, cblkno;
    opj_sparse_array_int32_t* sa = opj_sparse_array_int32_create(
                                       w, h, opj_uint_min(w, 64), opj_uint_min(h, 64));
    if (sa == NULL) {
        return NULL;
    }

    for (resno = 0; resno < numres; ++resno) {
        opj_tcd_resolution_t* res = &tilec->resolutions[resno];

        for (bandno = 0; bandno < res->numbands; ++bandno) {
            opj_tcd_band_t* band = &res->bands[bandno];

            for (precno = 0; precno < res->pw * res->ph; ++precno) {
                opj_tcd_precinct_t* precinct = &band->precincts[precno];
                for (cblkno = 0; cblkno < precinct->cw * precinct->ch; ++cblkno) {
                    opj_tcd_cblk_dec_t* cblk = &precinct->cblks.dec[cblkno];
                    if (cblk->decoded_data != NULL) {
                        OPJ_UINT32 x = (OPJ_UINT32)(cblk->x0 - band->x0);
                        OPJ_UINT32 y = (OPJ_UINT32)(cblk->y0 - band->y0);
                        OPJ_UINT32 cblk_w = (OPJ_UINT32)(cblk->x1 - cblk->x0);
                        OPJ_UINT32 cblk_h = (OPJ_UINT32)(cblk->y1 - cblk->y0);

                        if (band->bandno & 1) {
                            opj_tcd_resolution_t* pres = &tilec->resolutions[resno - 1];
                            x += (OPJ_UINT32)(pres->x1 - pres->x0);
                        }
                        if (band->bandno & 2) {
                            opj_tcd_resolution_t* pres = &tilec->resolutions[resno - 1];
                            y += (OPJ_UINT32)(pres->y1 - pres->y0);
                        }

                        if (!opj_sparse_array_int32_write(sa, x, y,
                                                          x + cblk_w, y + cblk_h,
                                                          cblk->decoded_data,
                                                          1, cblk_w, OPJ_TRUE)) {
                            opj_sparse_array_int32_free(sa);
                            return NULL;
                        }
                    }
                }
            }
        }
    }

    return sa;
}