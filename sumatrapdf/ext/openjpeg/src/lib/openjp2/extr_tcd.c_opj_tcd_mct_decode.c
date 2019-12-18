#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int mct; TYPE_1__* tccps; scalar_t__ m_mct_decoding_matrix; } ;
typedef  TYPE_5__ opj_tcp_t ;
struct TYPE_16__ {int minimum_num_resolutions; scalar_t__ data_win; scalar_t__ data; TYPE_9__* resolutions; } ;
typedef  TYPE_6__ opj_tcd_tilecomp_t ;
struct TYPE_17__ {int numcomps; TYPE_6__* comps; } ;
typedef  TYPE_7__ opj_tcd_tile_t ;
struct TYPE_18__ {scalar_t__ whole_tile_decoding; TYPE_4__* image; int /*<<< orphan*/ * used_component; TYPE_5__* tcp; TYPE_2__* tcd_image; } ;
typedef  TYPE_8__ opj_tcd_t ;
struct TYPE_19__ {int x1; int x0; int y1; int y0; size_t win_x1; size_t win_x0; size_t win_y1; size_t win_y0; } ;
typedef  TYPE_9__ opj_tcd_resolution_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_14__ {TYPE_3__* comps; } ;
struct TYPE_13__ {scalar_t__ resno_decoded; int /*<<< orphan*/  sgnd; } ;
struct TYPE_12__ {TYPE_7__* tiles; } ;
struct TYPE_11__ {int qmfbid; } ;
typedef  size_t OPJ_UINT32 ;
typedef  size_t OPJ_SIZE_T ;
typedef  int /*<<< orphan*/  OPJ_FLOAT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  opj_free (int /*<<< orphan*/ **) ; 
 scalar_t__ opj_malloc (int) ; 
 int /*<<< orphan*/  opj_mct_decode (scalar_t__,scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  opj_mct_decode_custom (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ **,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_mct_decode_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static OPJ_BOOL opj_tcd_mct_decode(opj_tcd_t *p_tcd, opj_event_mgr_t *p_manager)
{
    opj_tcd_tile_t * l_tile = p_tcd->tcd_image->tiles;
    opj_tcp_t * l_tcp = p_tcd->tcp;
    opj_tcd_tilecomp_t * l_tile_comp = l_tile->comps;
    OPJ_UINT32 l_samples, i;

    if (l_tcp->mct == 0 || p_tcd->used_component != NULL) {
        return OPJ_TRUE;
    }

    if (p_tcd->whole_tile_decoding) {
        opj_tcd_resolution_t* res_comp0 = l_tile->comps[0].resolutions +
                                          l_tile_comp->minimum_num_resolutions - 1;

        /* A bit inefficient: we process more data than needed if */
        /* resno_decoded < l_tile_comp->minimum_num_resolutions-1, */
        /* but we would need to take into account a stride then */
        l_samples = (OPJ_UINT32)((res_comp0->x1 - res_comp0->x0) *
                                 (res_comp0->y1 - res_comp0->y0));
        if (l_tile->numcomps >= 3) {
            if (l_tile_comp->minimum_num_resolutions !=
                    l_tile->comps[1].minimum_num_resolutions ||
                    l_tile_comp->minimum_num_resolutions !=
                    l_tile->comps[2].minimum_num_resolutions) {
                opj_event_msg(p_manager, EVT_ERROR,
                              "Tiles don't all have the same dimension. Skip the MCT step.\n");
                return OPJ_FALSE;
            }
        }
        if (l_tile->numcomps >= 3) {
            opj_tcd_resolution_t* res_comp1 = l_tile->comps[1].resolutions +
                                              l_tile_comp->minimum_num_resolutions - 1;
            opj_tcd_resolution_t* res_comp2 = l_tile->comps[2].resolutions +
                                              l_tile_comp->minimum_num_resolutions - 1;
            /* testcase 1336.pdf.asan.47.376 */
            if (p_tcd->image->comps[0].resno_decoded !=
                    p_tcd->image->comps[1].resno_decoded ||
                    p_tcd->image->comps[0].resno_decoded !=
                    p_tcd->image->comps[2].resno_decoded ||
                    (OPJ_SIZE_T)(res_comp1->x1 - res_comp1->x0) *
                    (OPJ_SIZE_T)(res_comp1->y1 - res_comp1->y0) != l_samples ||
                    (OPJ_SIZE_T)(res_comp2->x1 - res_comp2->x0) *
                    (OPJ_SIZE_T)(res_comp2->y1 - res_comp2->y0) != l_samples) {
                opj_event_msg(p_manager, EVT_ERROR,
                              "Tiles don't all have the same dimension. Skip the MCT step.\n");
                return OPJ_FALSE;
            }
        }
    } else {
        opj_tcd_resolution_t* res_comp0 = l_tile->comps[0].resolutions +
                                          p_tcd->image->comps[0].resno_decoded;

        l_samples = (res_comp0->win_x1 - res_comp0->win_x0) *
                    (res_comp0->win_y1 - res_comp0->win_y0);
        if (l_tile->numcomps >= 3) {
            opj_tcd_resolution_t* res_comp1 = l_tile->comps[1].resolutions +
                                              p_tcd->image->comps[1].resno_decoded;
            opj_tcd_resolution_t* res_comp2 = l_tile->comps[2].resolutions +
                                              p_tcd->image->comps[2].resno_decoded;
            /* testcase 1336.pdf.asan.47.376 */
            if (p_tcd->image->comps[0].resno_decoded !=
                    p_tcd->image->comps[1].resno_decoded ||
                    p_tcd->image->comps[0].resno_decoded !=
                    p_tcd->image->comps[2].resno_decoded ||
                    (OPJ_SIZE_T)(res_comp1->win_x1 - res_comp1->win_x0) *
                    (OPJ_SIZE_T)(res_comp1->win_y1 - res_comp1->win_y0) != l_samples ||
                    (OPJ_SIZE_T)(res_comp2->win_x1 - res_comp2->win_x0) *
                    (OPJ_SIZE_T)(res_comp2->win_y1 - res_comp2->win_y0) != l_samples) {
                opj_event_msg(p_manager, EVT_ERROR,
                              "Tiles don't all have the same dimension. Skip the MCT step.\n");
                return OPJ_FALSE;
            }
        }
    }

    if (l_tile->numcomps >= 3) {
        if (l_tcp->mct == 2) {
            OPJ_BYTE ** l_data;

            if (! l_tcp->m_mct_decoding_matrix) {
                return OPJ_TRUE;
            }

            l_data = (OPJ_BYTE **) opj_malloc(l_tile->numcomps * sizeof(OPJ_BYTE*));
            if (! l_data) {
                return OPJ_FALSE;
            }

            for (i = 0; i < l_tile->numcomps; ++i) {
                if (p_tcd->whole_tile_decoding) {
                    l_data[i] = (OPJ_BYTE*) l_tile_comp->data;
                } else {
                    l_data[i] = (OPJ_BYTE*) l_tile_comp->data_win;
                }
                ++l_tile_comp;
            }

            if (! opj_mct_decode_custom(/* MCT data */
                        (OPJ_BYTE*) l_tcp->m_mct_decoding_matrix,
                        /* size of components */
                        l_samples,
                        /* components */
                        l_data,
                        /* nb of components (i.e. size of pData) */
                        l_tile->numcomps,
                        /* tells if the data is signed */
                        p_tcd->image->comps->sgnd)) {
                opj_free(l_data);
                return OPJ_FALSE;
            }

            opj_free(l_data);
        } else {
            if (l_tcp->tccps->qmfbid == 1) {
                if (p_tcd->whole_tile_decoding) {
                    opj_mct_decode(l_tile->comps[0].data,
                                   l_tile->comps[1].data,
                                   l_tile->comps[2].data,
                                   l_samples);
                } else {
                    opj_mct_decode(l_tile->comps[0].data_win,
                                   l_tile->comps[1].data_win,
                                   l_tile->comps[2].data_win,
                                   l_samples);
                }
            } else {
                if (p_tcd->whole_tile_decoding) {
                    opj_mct_decode_real((OPJ_FLOAT32*)l_tile->comps[0].data,
                                        (OPJ_FLOAT32*)l_tile->comps[1].data,
                                        (OPJ_FLOAT32*)l_tile->comps[2].data,
                                        l_samples);
                } else {
                    opj_mct_decode_real((OPJ_FLOAT32*)l_tile->comps[0].data_win,
                                        (OPJ_FLOAT32*)l_tile->comps[1].data_win,
                                        (OPJ_FLOAT32*)l_tile->comps[2].data_win,
                                        l_samples);
                }
            }
        }
    } else {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Number of components (%d) is inconsistent with a MCT. Skip the MCT step.\n",
                      l_tile->numcomps);
    }

    return OPJ_TRUE;
}