#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ m_state; size_t m_start_tile_x; size_t m_start_tile_y; int m_end_tile_x; int m_end_tile_y; int m_discard_tiles; } ;
struct TYPE_18__ {TYPE_5__ m_decoder; } ;
struct TYPE_15__ {int /*<<< orphan*/  m_reduce; } ;
struct TYPE_16__ {TYPE_3__ m_dec; } ;
struct TYPE_21__ {int tw; int th; size_t tx0; size_t tdx; size_t ty0; size_t tdy; TYPE_4__ m_specific_param; TYPE_1__* tcps; } ;
struct TYPE_19__ {TYPE_6__ m_specific_param; TYPE_9__ m_cp; TYPE_8__* m_private_image; } ;
typedef  TYPE_7__ opj_j2k_t ;
struct TYPE_20__ {size_t numcomps; size_t x0; size_t y0; size_t x1; size_t y1; TYPE_2__* comps; } ;
typedef  TYPE_8__ opj_image_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  TYPE_9__ opj_cp_t ;
struct TYPE_14__ {int /*<<< orphan*/  factor; } ;
struct TYPE_13__ {int /*<<< orphan*/ * m_data; } ;
typedef  size_t OPJ_UINT32 ;
typedef  scalar_t__ OPJ_INT32 ;
typedef  scalar_t__ OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  EVT_INFO ; 
 int /*<<< orphan*/  EVT_WARNING ; 
 scalar_t__ J2K_STATE_TPHSOT ; 
 scalar_t__ OPJ_FALSE ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ opj_int_ceildiv (scalar_t__,scalar_t__) ; 
 scalar_t__ opj_j2k_update_image_dimensions (TYPE_8__*,int /*<<< orphan*/ *) ; 

OPJ_BOOL opj_j2k_set_decode_area(opj_j2k_t *p_j2k,
                                 opj_image_t* p_image,
                                 OPJ_INT32 p_start_x, OPJ_INT32 p_start_y,
                                 OPJ_INT32 p_end_x, OPJ_INT32 p_end_y,
                                 opj_event_mgr_t * p_manager)
{
    opj_cp_t * l_cp = &(p_j2k->m_cp);
    opj_image_t * l_image = p_j2k->m_private_image;
    OPJ_BOOL ret;
    OPJ_UINT32 it_comp;

    if (p_j2k->m_cp.tw == 1 && p_j2k->m_cp.th == 1 &&
            p_j2k->m_cp.tcps[0].m_data != NULL) {
        /* In the case of a single-tiled image whose codestream we have already */
        /* ingested, go on */
    }
    /* Check if we are read the main header */
    else if (p_j2k->m_specific_param.m_decoder.m_state != J2K_STATE_TPHSOT) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Need to decode the main header before begin to decode the remaining codestream.\n");
        return OPJ_FALSE;
    }

    /* Update the comps[].factor member of the output image with the one */
    /* of m_reduce */
    for (it_comp = 0; it_comp < p_image->numcomps; ++it_comp) {
        p_image->comps[it_comp].factor = p_j2k->m_cp.m_specific_param.m_dec.m_reduce;
    }

    if (!p_start_x && !p_start_y && !p_end_x && !p_end_y) {
        opj_event_msg(p_manager, EVT_INFO,
                      "No decoded area parameters, set the decoded area to the whole image\n");

        p_j2k->m_specific_param.m_decoder.m_start_tile_x = 0;
        p_j2k->m_specific_param.m_decoder.m_start_tile_y = 0;
        p_j2k->m_specific_param.m_decoder.m_end_tile_x = l_cp->tw;
        p_j2k->m_specific_param.m_decoder.m_end_tile_y = l_cp->th;

        p_image->x0 = l_image->x0;
        p_image->y0 = l_image->y0;
        p_image->x1 = l_image->x1;
        p_image->y1 = l_image->y1;

        return opj_j2k_update_image_dimensions(p_image, p_manager);
    }

    /* ----- */
    /* Check if the positions provided by the user are correct */

    /* Left */
    if (p_start_x < 0) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Left position of the decoded area (region_x0=%d) should be >= 0.\n",
                      p_start_x);
        return OPJ_FALSE;
    } else if ((OPJ_UINT32)p_start_x > l_image->x1) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Left position of the decoded area (region_x0=%d) is outside the image area (Xsiz=%d).\n",
                      p_start_x, l_image->x1);
        return OPJ_FALSE;
    } else if ((OPJ_UINT32)p_start_x < l_image->x0) {
        opj_event_msg(p_manager, EVT_WARNING,
                      "Left position of the decoded area (region_x0=%d) is outside the image area (XOsiz=%d).\n",
                      p_start_x, l_image->x0);
        p_j2k->m_specific_param.m_decoder.m_start_tile_x = 0;
        p_image->x0 = l_image->x0;
    } else {
        p_j2k->m_specific_param.m_decoder.m_start_tile_x = ((OPJ_UINT32)p_start_x -
                l_cp->tx0) / l_cp->tdx;
        p_image->x0 = (OPJ_UINT32)p_start_x;
    }

    /* Up */
    if (p_start_y < 0) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Up position of the decoded area (region_y0=%d) should be >= 0.\n",
                      p_start_y);
        return OPJ_FALSE;
    } else if ((OPJ_UINT32)p_start_y > l_image->y1) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Up position of the decoded area (region_y0=%d) is outside the image area (Ysiz=%d).\n",
                      p_start_y, l_image->y1);
        return OPJ_FALSE;
    } else if ((OPJ_UINT32)p_start_y < l_image->y0) {
        opj_event_msg(p_manager, EVT_WARNING,
                      "Up position of the decoded area (region_y0=%d) is outside the image area (YOsiz=%d).\n",
                      p_start_y, l_image->y0);
        p_j2k->m_specific_param.m_decoder.m_start_tile_y = 0;
        p_image->y0 = l_image->y0;
    } else {
        p_j2k->m_specific_param.m_decoder.m_start_tile_y = ((OPJ_UINT32)p_start_y -
                l_cp->ty0) / l_cp->tdy;
        p_image->y0 = (OPJ_UINT32)p_start_y;
    }

    /* Right */
    if (p_end_x <= 0) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Right position of the decoded area (region_x1=%d) should be > 0.\n",
                      p_end_x);
        return OPJ_FALSE;
    } else if ((OPJ_UINT32)p_end_x < l_image->x0) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Right position of the decoded area (region_x1=%d) is outside the image area (XOsiz=%d).\n",
                      p_end_x, l_image->x0);
        return OPJ_FALSE;
    } else if ((OPJ_UINT32)p_end_x > l_image->x1) {
        opj_event_msg(p_manager, EVT_WARNING,
                      "Right position of the decoded area (region_x1=%d) is outside the image area (Xsiz=%d).\n",
                      p_end_x, l_image->x1);
        p_j2k->m_specific_param.m_decoder.m_end_tile_x = l_cp->tw;
        p_image->x1 = l_image->x1;
    } else {
        p_j2k->m_specific_param.m_decoder.m_end_tile_x = (OPJ_UINT32)opj_int_ceildiv(
                    p_end_x - (OPJ_INT32)l_cp->tx0, (OPJ_INT32)l_cp->tdx);
        p_image->x1 = (OPJ_UINT32)p_end_x;
    }

    /* Bottom */
    if (p_end_y <= 0) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Bottom position of the decoded area (region_y1=%d) should be > 0.\n",
                      p_end_y);
        return OPJ_FALSE;
    } else if ((OPJ_UINT32)p_end_y < l_image->y0) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Bottom position of the decoded area (region_y1=%d) is outside the image area (YOsiz=%d).\n",
                      p_end_y, l_image->y0);
        return OPJ_FALSE;
    }
    if ((OPJ_UINT32)p_end_y > l_image->y1) {
        opj_event_msg(p_manager, EVT_WARNING,
                      "Bottom position of the decoded area (region_y1=%d) is outside the image area (Ysiz=%d).\n",
                      p_end_y, l_image->y1);
        p_j2k->m_specific_param.m_decoder.m_end_tile_y = l_cp->th;
        p_image->y1 = l_image->y1;
    } else {
        p_j2k->m_specific_param.m_decoder.m_end_tile_y = (OPJ_UINT32)opj_int_ceildiv(
                    p_end_y - (OPJ_INT32)l_cp->ty0, (OPJ_INT32)l_cp->tdy);
        p_image->y1 = (OPJ_UINT32)p_end_y;
    }
    /* ----- */

    p_j2k->m_specific_param.m_decoder.m_discard_tiles = 1;

    ret = opj_j2k_update_image_dimensions(p_image, p_manager);

    if (ret) {
        opj_event_msg(p_manager, EVT_INFO, "Setting decoding area to %d,%d,%d,%d\n",
                      p_image->x0, p_image->y0, p_image->x1, p_image->y1);
    }

    return ret;
}