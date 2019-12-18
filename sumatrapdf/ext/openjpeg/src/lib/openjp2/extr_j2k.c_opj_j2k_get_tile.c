#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_stream_private_t ;
struct TYPE_19__ {scalar_t__ m_tile_ind_to_dec; } ;
struct TYPE_20__ {TYPE_1__ m_decoder; } ;
struct TYPE_21__ {int tw; int th; int tdx; scalar_t__ tx0; int tdy; scalar_t__ ty0; } ;
struct TYPE_23__ {TYPE_14__* m_private_image; int /*<<< orphan*/  m_procedure_list; TYPE_2__ m_specific_param; TYPE_14__* m_output_image; TYPE_3__ m_cp; } ;
typedef  TYPE_5__ opj_j2k_t ;
struct TYPE_24__ {int numcomps; scalar_t__ x0; scalar_t__ x1; scalar_t__ y0; scalar_t__ y1; TYPE_7__* comps; } ;
typedef  TYPE_6__ opj_image_t ;
struct TYPE_25__ {int x0; int y0; int w; int h; int /*<<< orphan*/ * data; scalar_t__ factor; scalar_t__ dy; scalar_t__ dx; } ;
typedef  TYPE_7__ opj_image_comp_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
struct TYPE_22__ {scalar_t__ factor; } ;
struct TYPE_18__ {int numcomps; scalar_t__ x0; scalar_t__ x1; scalar_t__ y0; scalar_t__ y1; TYPE_4__* comps; } ;
typedef  int OPJ_UINT32 ;
typedef  scalar_t__ OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  opj_copy_image_header (TYPE_6__*,TYPE_14__*) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_14__* opj_image_create0 () ; 
 int /*<<< orphan*/  opj_image_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_image_destroy (TYPE_14__*) ; 
 scalar_t__ opj_int_ceildiv (scalar_t__,scalar_t__) ; 
 scalar_t__ opj_int_ceildivpow2 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  opj_j2k_exec (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_j2k_move_data_from_codec_to_output_image (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  opj_j2k_setup_decoding_tile (TYPE_5__*,int /*<<< orphan*/ *) ; 

OPJ_BOOL opj_j2k_get_tile(opj_j2k_t *p_j2k,
                          opj_stream_private_t *p_stream,
                          opj_image_t* p_image,
                          opj_event_mgr_t * p_manager,
                          OPJ_UINT32 tile_index)
{
    OPJ_UINT32 compno;
    OPJ_UINT32 l_tile_x, l_tile_y;
    opj_image_comp_t* l_img_comp;

    if (!p_image) {
        opj_event_msg(p_manager, EVT_ERROR, "We need an image previously created.\n");
        return OPJ_FALSE;
    }

    if (p_image->numcomps < p_j2k->m_private_image->numcomps) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Image has less components than codestream.\n");
        return OPJ_FALSE;
    }

    if (/*(tile_index < 0) &&*/ (tile_index >= p_j2k->m_cp.tw * p_j2k->m_cp.th)) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Tile index provided by the user is incorrect %d (max = %d) \n", tile_index,
                      (p_j2k->m_cp.tw * p_j2k->m_cp.th) - 1);
        return OPJ_FALSE;
    }

    /* Compute the dimension of the desired tile*/
    l_tile_x = tile_index % p_j2k->m_cp.tw;
    l_tile_y = tile_index / p_j2k->m_cp.tw;

    p_image->x0 = l_tile_x * p_j2k->m_cp.tdx + p_j2k->m_cp.tx0;
    if (p_image->x0 < p_j2k->m_private_image->x0) {
        p_image->x0 = p_j2k->m_private_image->x0;
    }
    p_image->x1 = (l_tile_x + 1) * p_j2k->m_cp.tdx + p_j2k->m_cp.tx0;
    if (p_image->x1 > p_j2k->m_private_image->x1) {
        p_image->x1 = p_j2k->m_private_image->x1;
    }

    p_image->y0 = l_tile_y * p_j2k->m_cp.tdy + p_j2k->m_cp.ty0;
    if (p_image->y0 < p_j2k->m_private_image->y0) {
        p_image->y0 = p_j2k->m_private_image->y0;
    }
    p_image->y1 = (l_tile_y + 1) * p_j2k->m_cp.tdy + p_j2k->m_cp.ty0;
    if (p_image->y1 > p_j2k->m_private_image->y1) {
        p_image->y1 = p_j2k->m_private_image->y1;
    }

    l_img_comp = p_image->comps;
    for (compno = 0; compno < p_j2k->m_private_image->numcomps; ++compno) {
        OPJ_INT32 l_comp_x1, l_comp_y1;

        l_img_comp->factor = p_j2k->m_private_image->comps[compno].factor;

        l_img_comp->x0 = (OPJ_UINT32)opj_int_ceildiv((OPJ_INT32)p_image->x0,
                         (OPJ_INT32)l_img_comp->dx);
        l_img_comp->y0 = (OPJ_UINT32)opj_int_ceildiv((OPJ_INT32)p_image->y0,
                         (OPJ_INT32)l_img_comp->dy);
        l_comp_x1 = opj_int_ceildiv((OPJ_INT32)p_image->x1, (OPJ_INT32)l_img_comp->dx);
        l_comp_y1 = opj_int_ceildiv((OPJ_INT32)p_image->y1, (OPJ_INT32)l_img_comp->dy);

        l_img_comp->w = (OPJ_UINT32)(opj_int_ceildivpow2(l_comp_x1,
                                     (OPJ_INT32)l_img_comp->factor) - opj_int_ceildivpow2((OPJ_INT32)l_img_comp->x0,
                                             (OPJ_INT32)l_img_comp->factor));
        l_img_comp->h = (OPJ_UINT32)(opj_int_ceildivpow2(l_comp_y1,
                                     (OPJ_INT32)l_img_comp->factor) - opj_int_ceildivpow2((OPJ_INT32)l_img_comp->y0,
                                             (OPJ_INT32)l_img_comp->factor));

        l_img_comp++;
    }

    if (p_image->numcomps > p_j2k->m_private_image->numcomps) {
        /* Can happen when calling repeatdly opj_get_decoded_tile() on an
         * image with a color palette, where color palette expansion is done
         * later in jp2.c */
        for (compno = p_j2k->m_private_image->numcomps; compno < p_image->numcomps;
                ++compno) {
            opj_image_data_free(p_image->comps[compno].data);
            p_image->comps[compno].data = NULL;
        }
        p_image->numcomps = p_j2k->m_private_image->numcomps;
    }

    /* Destroy the previous output image*/
    if (p_j2k->m_output_image) {
        opj_image_destroy(p_j2k->m_output_image);
    }

    /* Create the ouput image from the information previously computed*/
    p_j2k->m_output_image = opj_image_create0();
    if (!(p_j2k->m_output_image)) {
        return OPJ_FALSE;
    }
    opj_copy_image_header(p_image, p_j2k->m_output_image);

    p_j2k->m_specific_param.m_decoder.m_tile_ind_to_dec = (OPJ_INT32)tile_index;

    /* customization of the decoding */
    if (!opj_j2k_setup_decoding_tile(p_j2k, p_manager)) {
        return OPJ_FALSE;
    }

    /* Decode the codestream */
    if (! opj_j2k_exec(p_j2k, p_j2k->m_procedure_list, p_stream, p_manager)) {
        opj_image_destroy(p_j2k->m_private_image);
        p_j2k->m_private_image = NULL;
        return OPJ_FALSE;
    }

    /* Move data and copy one information from codec to output image*/
    return opj_j2k_move_data_from_codec_to_output_image(p_j2k, p_image);
}