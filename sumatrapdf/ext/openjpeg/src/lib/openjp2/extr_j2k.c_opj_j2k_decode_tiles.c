#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_stream_private_t ;
struct TYPE_31__ {int tw; int th; scalar_t__ tx0; scalar_t__ ty0; scalar_t__ tdx; scalar_t__ tdy; TYPE_14__* tcps; } ;
struct TYPE_29__ {int /*<<< orphan*/  m_state; } ;
struct TYPE_30__ {TYPE_7__ m_decoder; } ;
struct TYPE_19__ {TYPE_9__ m_cp; TYPE_8__ m_specific_param; TYPE_10__* m_private_image; TYPE_13__* m_output_image; TYPE_12__* m_tcd; scalar_t__ m_current_tile_number; } ;
typedef  TYPE_11__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_28__ {TYPE_5__* tiles; } ;
struct TYPE_27__ {TYPE_4__* comps; } ;
struct TYPE_26__ {int /*<<< orphan*/ * data; } ;
struct TYPE_25__ {TYPE_2__* comps; } ;
struct TYPE_24__ {int /*<<< orphan*/  resno_decoded; } ;
struct TYPE_23__ {int /*<<< orphan*/  resno_decoded; int /*<<< orphan*/ * data; } ;
struct TYPE_22__ {int /*<<< orphan*/ * m_data; } ;
struct TYPE_21__ {scalar_t__ x0; scalar_t__ y0; scalar_t__ x1; scalar_t__ y1; size_t numcomps; TYPE_1__* comps; } ;
struct TYPE_20__ {TYPE_6__* tcd_image; TYPE_3__* image; } ;
struct TYPE_18__ {scalar_t__ x0; scalar_t__ y0; scalar_t__ x1; scalar_t__ y1; } ;
typedef  size_t OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  EVT_INFO ; 
 int /*<<< orphan*/  J2K_STATE_DATA ; 
 int /*<<< orphan*/  J2K_STATE_NEOC ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  opj_image_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_j2k_decode_tile (TYPE_11__*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_j2k_read_tile_header (TYPE_11__*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_j2k_tcp_data_destroy (TYPE_14__*) ; 
 int /*<<< orphan*/  opj_j2k_update_image_data (TYPE_12__*,TYPE_13__*) ; 
 scalar_t__ opj_stream_get_number_byte_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static OPJ_BOOL opj_j2k_decode_tiles(opj_j2k_t *p_j2k,
                                     opj_stream_private_t *p_stream,
                                     opj_event_mgr_t * p_manager)
{
    OPJ_BOOL l_go_on = OPJ_TRUE;
    OPJ_UINT32 l_current_tile_no;
    OPJ_INT32 l_tile_x0, l_tile_y0, l_tile_x1, l_tile_y1;
    OPJ_UINT32 l_nb_comps;
    OPJ_UINT32 nr_tiles = 0;

    /* Particular case for whole single tile decoding */
    /* We can avoid allocating intermediate tile buffers */
    if (p_j2k->m_cp.tw == 1 && p_j2k->m_cp.th == 1 &&
            p_j2k->m_cp.tx0 == 0 && p_j2k->m_cp.ty0 == 0 &&
            p_j2k->m_output_image->x0 == 0 &&
            p_j2k->m_output_image->y0 == 0 &&
            p_j2k->m_output_image->x1 == p_j2k->m_cp.tdx &&
            p_j2k->m_output_image->y1 == p_j2k->m_cp.tdy) {
        OPJ_UINT32 i;
        if (! opj_j2k_read_tile_header(p_j2k,
                                       &l_current_tile_no,
                                       NULL,
                                       &l_tile_x0, &l_tile_y0,
                                       &l_tile_x1, &l_tile_y1,
                                       &l_nb_comps,
                                       &l_go_on,
                                       p_stream,
                                       p_manager)) {
            return OPJ_FALSE;
        }

        if (! opj_j2k_decode_tile(p_j2k, l_current_tile_no, NULL, 0,
                                  p_stream, p_manager)) {
            opj_event_msg(p_manager, EVT_ERROR, "Failed to decode tile 1/1\n");
            return OPJ_FALSE;
        }

        /* Transfer TCD data to output image data */
        for (i = 0; i < p_j2k->m_output_image->numcomps; i++) {
            opj_image_data_free(p_j2k->m_output_image->comps[i].data);
            p_j2k->m_output_image->comps[i].data =
                p_j2k->m_tcd->tcd_image->tiles->comps[i].data;
            p_j2k->m_output_image->comps[i].resno_decoded =
                p_j2k->m_tcd->image->comps[i].resno_decoded;
            p_j2k->m_tcd->tcd_image->tiles->comps[i].data = NULL;
        }

        return OPJ_TRUE;
    }

    for (;;) {
        if (p_j2k->m_cp.tw == 1 && p_j2k->m_cp.th == 1 &&
                p_j2k->m_cp.tcps[0].m_data != NULL) {
            l_current_tile_no = 0;
            p_j2k->m_current_tile_number = 0;
            p_j2k->m_specific_param.m_decoder.m_state |= J2K_STATE_DATA;
        } else {
            if (! opj_j2k_read_tile_header(p_j2k,
                                           &l_current_tile_no,
                                           NULL,
                                           &l_tile_x0, &l_tile_y0,
                                           &l_tile_x1, &l_tile_y1,
                                           &l_nb_comps,
                                           &l_go_on,
                                           p_stream,
                                           p_manager)) {
                return OPJ_FALSE;
            }

            if (! l_go_on) {
                break;
            }
        }

        if (! opj_j2k_decode_tile(p_j2k, l_current_tile_no, NULL, 0,
                                  p_stream, p_manager)) {
            opj_event_msg(p_manager, EVT_ERROR, "Failed to decode tile %d/%d\n",
                          l_current_tile_no + 1, p_j2k->m_cp.th * p_j2k->m_cp.tw);
            return OPJ_FALSE;
        }

        opj_event_msg(p_manager, EVT_INFO, "Tile %d/%d has been decoded.\n",
                      l_current_tile_no + 1, p_j2k->m_cp.th * p_j2k->m_cp.tw);

        if (! opj_j2k_update_image_data(p_j2k->m_tcd,
                                        p_j2k->m_output_image)) {
            return OPJ_FALSE;
        }

        if (p_j2k->m_cp.tw == 1 && p_j2k->m_cp.th == 1 &&
                !(p_j2k->m_output_image->x0 == p_j2k->m_private_image->x0 &&
                  p_j2k->m_output_image->y0 == p_j2k->m_private_image->y0 &&
                  p_j2k->m_output_image->x1 == p_j2k->m_private_image->x1 &&
                  p_j2k->m_output_image->y1 == p_j2k->m_private_image->y1)) {
            /* Keep current tcp data */
        } else {
            opj_j2k_tcp_data_destroy(&p_j2k->m_cp.tcps[l_current_tile_no]);
        }

        opj_event_msg(p_manager, EVT_INFO,
                      "Image data has been updated with tile %d.\n\n", l_current_tile_no + 1);

        if (opj_stream_get_number_byte_left(p_stream) == 0
                && p_j2k->m_specific_param.m_decoder.m_state == J2K_STATE_NEOC) {
            break;
        }
        if (++nr_tiles ==  p_j2k->m_cp.th * p_j2k->m_cp.tw) {
            break;
        }
    }

    return OPJ_TRUE;
}