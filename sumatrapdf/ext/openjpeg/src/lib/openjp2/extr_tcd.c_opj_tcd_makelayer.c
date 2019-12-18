#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {size_t numresolutions; TYPE_6__* resolutions; } ;
typedef  TYPE_3__ opj_tcd_tilecomp_t ;
struct TYPE_19__ {scalar_t__* distolayer; size_t numcomps; TYPE_3__* comps; } ;
typedef  TYPE_4__ opj_tcd_tile_t ;
struct TYPE_20__ {TYPE_1__* tcd_image; } ;
typedef  TYPE_5__ opj_tcd_t ;
struct TYPE_21__ {size_t numbands; size_t pw; size_t ph; TYPE_11__* bands; } ;
typedef  TYPE_6__ opj_tcd_resolution_t ;
struct TYPE_17__ {TYPE_10__* enc; } ;
struct TYPE_22__ {size_t cw; size_t ch; TYPE_2__ cblks; } ;
typedef  TYPE_7__ opj_tcd_precinct_t ;
struct TYPE_23__ {size_t rate; scalar_t__ distortiondec; } ;
typedef  TYPE_8__ opj_tcd_pass_t ;
struct TYPE_24__ {size_t numpasses; scalar_t__ disto; size_t len; size_t data; } ;
typedef  TYPE_9__ opj_tcd_layer_t ;
struct TYPE_14__ {size_t numpassesinlayers; size_t totalpasses; size_t data; TYPE_8__* passes; TYPE_9__* layers; } ;
typedef  TYPE_10__ opj_tcd_cblk_enc_t ;
struct TYPE_15__ {TYPE_7__* precincts; } ;
typedef  TYPE_11__ opj_tcd_band_t ;
struct TYPE_16__ {TYPE_4__* tiles; } ;
typedef  size_t OPJ_UINT32 ;
typedef  scalar_t__ OPJ_FLOAT64 ;

/* Variables and functions */
 scalar_t__ DBL_EPSILON ; 
 scalar_t__ opj_tcd_is_band_empty (TYPE_11__*) ; 

void opj_tcd_makelayer(opj_tcd_t *tcd,
                       OPJ_UINT32 layno,
                       OPJ_FLOAT64 thresh,
                       OPJ_UINT32 final)
{
    OPJ_UINT32 compno, resno, bandno, precno, cblkno;
    OPJ_UINT32 passno;

    opj_tcd_tile_t *tcd_tile = tcd->tcd_image->tiles;

    tcd_tile->distolayer[layno] = 0;        /* fixed_quality */

    for (compno = 0; compno < tcd_tile->numcomps; compno++) {
        opj_tcd_tilecomp_t *tilec = &tcd_tile->comps[compno];

        for (resno = 0; resno < tilec->numresolutions; resno++) {
            opj_tcd_resolution_t *res = &tilec->resolutions[resno];

            for (bandno = 0; bandno < res->numbands; bandno++) {
                opj_tcd_band_t *band = &res->bands[bandno];

                /* Skip empty bands */
                if (opj_tcd_is_band_empty(band)) {
                    continue;
                }

                for (precno = 0; precno < res->pw * res->ph; precno++) {
                    opj_tcd_precinct_t *prc = &band->precincts[precno];

                    for (cblkno = 0; cblkno < prc->cw * prc->ch; cblkno++) {
                        opj_tcd_cblk_enc_t *cblk = &prc->cblks.enc[cblkno];
                        opj_tcd_layer_t *layer = &cblk->layers[layno];
                        OPJ_UINT32 n;

                        if (layno == 0) {
                            cblk->numpassesinlayers = 0;
                        }

                        n = cblk->numpassesinlayers;

                        if (thresh < 0) {
                            /* Special value to indicate to use all passes */
                            n = cblk->totalpasses;
                        } else {
                            for (passno = cblk->numpassesinlayers; passno < cblk->totalpasses; passno++) {
                                OPJ_UINT32 dr;
                                OPJ_FLOAT64 dd;
                                opj_tcd_pass_t *pass = &cblk->passes[passno];

                                if (n == 0) {
                                    dr = pass->rate;
                                    dd = pass->distortiondec;
                                } else {
                                    dr = pass->rate - cblk->passes[n - 1].rate;
                                    dd = pass->distortiondec - cblk->passes[n - 1].distortiondec;
                                }

                                if (!dr) {
                                    if (dd != 0) {
                                        n = passno + 1;
                                    }
                                    continue;
                                }
                                if (thresh - (dd / dr) <
                                        DBL_EPSILON) { /* do not rely on float equality, check with DBL_EPSILON margin */
                                    n = passno + 1;
                                }
                            }
                        }

                        layer->numpasses = n - cblk->numpassesinlayers;

                        if (!layer->numpasses) {
                            layer->disto = 0;
                            continue;
                        }

                        if (cblk->numpassesinlayers == 0) {
                            layer->len = cblk->passes[n - 1].rate;
                            layer->data = cblk->data;
                            layer->disto = cblk->passes[n - 1].distortiondec;
                        } else {
                            layer->len = cblk->passes[n - 1].rate - cblk->passes[cblk->numpassesinlayers -
                                         1].rate;
                            layer->data = cblk->data + cblk->passes[cblk->numpassesinlayers - 1].rate;
                            layer->disto = cblk->passes[n - 1].distortiondec -
                                           cblk->passes[cblk->numpassesinlayers - 1].distortiondec;
                        }

                        tcd_tile->distolayer[layno] += layer->disto;    /* fixed_quality */

                        if (final) {
                            cblk->numpassesinlayers = n;
                        }
                    }
                }
            }
        }
    }
}