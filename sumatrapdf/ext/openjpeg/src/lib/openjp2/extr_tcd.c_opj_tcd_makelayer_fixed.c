#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_17__ ;
typedef  struct TYPE_26__   TYPE_16__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_35__ {size_t numlayers; } ;
typedef  TYPE_8__ opj_tcp_t ;
struct TYPE_36__ {size_t numresolutions; TYPE_12__* resolutions; } ;
typedef  TYPE_9__ opj_tcd_tilecomp_t ;
struct TYPE_20__ {size_t numcomps; TYPE_9__* comps; } ;
typedef  TYPE_10__ opj_tcd_tile_t ;
struct TYPE_21__ {TYPE_6__* image; TYPE_8__* tcp; TYPE_1__* tcd_image; TYPE_17__* cp; } ;
typedef  TYPE_11__ opj_tcd_t ;
struct TYPE_22__ {size_t numbands; size_t pw; size_t ph; TYPE_16__* bands; } ;
typedef  TYPE_12__ opj_tcd_resolution_t ;
struct TYPE_31__ {TYPE_15__* enc; } ;
struct TYPE_23__ {size_t cw; size_t ch; TYPE_4__ cblks; } ;
typedef  TYPE_13__ opj_tcd_precinct_t ;
struct TYPE_24__ {size_t numpasses; scalar_t__ data; scalar_t__ len; } ;
typedef  TYPE_14__ opj_tcd_layer_t ;
struct TYPE_25__ {size_t numpassesinlayers; TYPE_7__* passes; scalar_t__ data; scalar_t__ numbps; TYPE_14__* layers; } ;
typedef  TYPE_15__ opj_tcd_cblk_enc_t ;
struct TYPE_26__ {TYPE_13__* precincts; } ;
typedef  TYPE_16__ opj_tcd_band_t ;
struct TYPE_29__ {scalar_t__* m_matrice; } ;
struct TYPE_30__ {TYPE_2__ m_enc; } ;
struct TYPE_27__ {TYPE_3__ m_specific_param; } ;
typedef  TYPE_17__ opj_cp_t ;
struct TYPE_34__ {scalar_t__ rate; } ;
struct TYPE_33__ {TYPE_5__* comps; } ;
struct TYPE_32__ {double prec; } ;
struct TYPE_28__ {TYPE_10__* tiles; } ;
typedef  size_t OPJ_UINT32 ;
typedef  scalar_t__ OPJ_INT32 ;
typedef  int OPJ_FLOAT32 ;

/* Variables and functions */
 scalar_t__ opj_tcd_is_band_empty (TYPE_16__*) ; 

void opj_tcd_makelayer_fixed(opj_tcd_t *tcd, OPJ_UINT32 layno,
                             OPJ_UINT32 final)
{
    OPJ_UINT32 compno, resno, bandno, precno, cblkno;
    OPJ_INT32 value;                        /*, matrice[tcd_tcp->numlayers][tcd_tile->comps[0].numresolutions][3]; */
    OPJ_INT32 matrice[10][10][3];
    OPJ_UINT32 i, j, k;

    opj_cp_t *cp = tcd->cp;
    opj_tcd_tile_t *tcd_tile = tcd->tcd_image->tiles;
    opj_tcp_t *tcd_tcp = tcd->tcp;

    for (compno = 0; compno < tcd_tile->numcomps; compno++) {
        opj_tcd_tilecomp_t *tilec = &tcd_tile->comps[compno];

        for (i = 0; i < tcd_tcp->numlayers; i++) {
            for (j = 0; j < tilec->numresolutions; j++) {
                for (k = 0; k < 3; k++) {
                    matrice[i][j][k] =
                        (OPJ_INT32)((OPJ_FLOAT32)cp->m_specific_param.m_enc.m_matrice[i *
                                      tilec->numresolutions * 3 + j * 3 + k]
                                    * (OPJ_FLOAT32)(tcd->image->comps[compno].prec / 16.0));
                }
            }
        }

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
                        OPJ_INT32 imsb = (OPJ_INT32)(tcd->image->comps[compno].prec -
                                                     cblk->numbps); /* number of bit-plan equal to zero */

                        /* Correction of the matrix of coefficient to include the IMSB information */
                        if (layno == 0) {
                            value = matrice[layno][resno][bandno];
                            if (imsb >= value) {
                                value = 0;
                            } else {
                                value -= imsb;
                            }
                        } else {
                            value = matrice[layno][resno][bandno] - matrice[layno - 1][resno][bandno];
                            if (imsb >= matrice[layno - 1][resno][bandno]) {
                                value -= (imsb - matrice[layno - 1][resno][bandno]);
                                if (value < 0) {
                                    value = 0;
                                }
                            }
                        }

                        if (layno == 0) {
                            cblk->numpassesinlayers = 0;
                        }

                        n = cblk->numpassesinlayers;
                        if (cblk->numpassesinlayers == 0) {
                            if (value != 0) {
                                n = 3 * (OPJ_UINT32)value - 2 + cblk->numpassesinlayers;
                            } else {
                                n = cblk->numpassesinlayers;
                            }
                        } else {
                            n = 3 * (OPJ_UINT32)value + cblk->numpassesinlayers;
                        }

                        layer->numpasses = n - cblk->numpassesinlayers;

                        if (!layer->numpasses) {
                            continue;
                        }

                        if (cblk->numpassesinlayers == 0) {
                            layer->len = cblk->passes[n - 1].rate;
                            layer->data = cblk->data;
                        } else {
                            layer->len = cblk->passes[n - 1].rate - cblk->passes[cblk->numpassesinlayers -
                                         1].rate;
                            layer->data = cblk->data + cblk->passes[cblk->numpassesinlayers - 1].rate;
                        }

                        if (final) {
                            cblk->numpassesinlayers = n;
                        }
                    }
                }
            }
        }
    }
}