#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int minimum_num_resolutions; scalar_t__* data; scalar_t__* data_win; TYPE_5__* resolutions; } ;
typedef  TYPE_3__ opj_tcd_tilecomp_t ;
struct TYPE_13__ {scalar_t__ whole_tile_decoding; TYPE_6__* image; TYPE_2__* tcd_image; } ;
typedef  TYPE_4__ opj_tcd_t ;
struct TYPE_14__ {scalar_t__ x0; scalar_t__ y0; scalar_t__ x1; scalar_t__ y1; scalar_t__ win_x0; scalar_t__ win_x1; scalar_t__ win_y1; scalar_t__ win_y0; } ;
typedef  TYPE_5__ opj_tcd_resolution_t ;
struct TYPE_15__ {scalar_t__ numcomps; TYPE_7__* comps; } ;
typedef  TYPE_6__ opj_image_t ;
struct TYPE_16__ {int resno_decoded; scalar_t__ w; scalar_t__ h; scalar_t__* data; int /*<<< orphan*/  factor; int /*<<< orphan*/  y0; int /*<<< orphan*/  x0; } ;
typedef  TYPE_7__ opj_image_comp_t ;
struct TYPE_11__ {TYPE_1__* tiles; } ;
struct TYPE_10__ {TYPE_3__* comps; } ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  scalar_t__ OPJ_SIZE_T ;
typedef  scalar_t__ OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ opj_image_data_alloc (scalar_t__) ; 
 scalar_t__ opj_uint_ceildivpow2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OPJ_BOOL opj_j2k_update_image_data(opj_tcd_t * p_tcd,
        opj_image_t* p_output_image)
{
    OPJ_UINT32 i, j;
    OPJ_UINT32 l_width_src, l_height_src;
    OPJ_UINT32 l_width_dest, l_height_dest;
    OPJ_INT32 l_offset_x0_src, l_offset_y0_src, l_offset_x1_src, l_offset_y1_src;
    OPJ_SIZE_T l_start_offset_src;
    OPJ_UINT32 l_start_x_dest, l_start_y_dest;
    OPJ_UINT32 l_x0_dest, l_y0_dest, l_x1_dest, l_y1_dest;
    OPJ_SIZE_T l_start_offset_dest;

    opj_image_comp_t * l_img_comp_src = 00;
    opj_image_comp_t * l_img_comp_dest = 00;

    opj_tcd_tilecomp_t * l_tilec = 00;
    opj_image_t * l_image_src = 00;
    OPJ_INT32 * l_dest_ptr;

    l_tilec = p_tcd->tcd_image->tiles->comps;
    l_image_src = p_tcd->image;
    l_img_comp_src = l_image_src->comps;

    l_img_comp_dest = p_output_image->comps;

    for (i = 0; i < l_image_src->numcomps;
            i++, ++l_img_comp_dest, ++l_img_comp_src,  ++l_tilec) {
        OPJ_INT32 res_x0, res_x1, res_y0, res_y1;
        OPJ_UINT32 src_data_stride;
        const OPJ_INT32* p_src_data;

        /* Copy info from decoded comp image to output image */
        l_img_comp_dest->resno_decoded = l_img_comp_src->resno_decoded;

        if (p_tcd->whole_tile_decoding) {
            opj_tcd_resolution_t* l_res = l_tilec->resolutions +
                                          l_img_comp_src->resno_decoded;
            res_x0 = l_res->x0;
            res_y0 = l_res->y0;
            res_x1 = l_res->x1;
            res_y1 = l_res->y1;
            src_data_stride = (OPJ_UINT32)(
                                  l_tilec->resolutions[l_tilec->minimum_num_resolutions - 1].x1 -
                                  l_tilec->resolutions[l_tilec->minimum_num_resolutions - 1].x0);
            p_src_data = l_tilec->data;
        } else {
            opj_tcd_resolution_t* l_res = l_tilec->resolutions +
                                          l_img_comp_src->resno_decoded;
            res_x0 = (OPJ_INT32)l_res->win_x0;
            res_y0 = (OPJ_INT32)l_res->win_y0;
            res_x1 = (OPJ_INT32)l_res->win_x1;
            res_y1 = (OPJ_INT32)l_res->win_y1;
            src_data_stride = l_res->win_x1 - l_res->win_x0;
            p_src_data = l_tilec->data_win;
        }

        if (p_src_data == NULL) {
            /* Happens for partial component decoding */
            continue;
        }

        l_width_src = (OPJ_UINT32)(res_x1 - res_x0);
        l_height_src = (OPJ_UINT32)(res_y1 - res_y0);


        /* Current tile component size*/
        /*if (i == 0) {
        fprintf(stdout, "SRC: l_res_x0=%d, l_res_x1=%d, l_res_y0=%d, l_res_y1=%d\n",
                        res_x0, res_x1, res_y0, res_y1);
        }*/


        /* Border of the current output component*/
        l_x0_dest = opj_uint_ceildivpow2(l_img_comp_dest->x0, l_img_comp_dest->factor);
        l_y0_dest = opj_uint_ceildivpow2(l_img_comp_dest->y0, l_img_comp_dest->factor);
        l_x1_dest = l_x0_dest +
                    l_img_comp_dest->w; /* can't overflow given that image->x1 is uint32 */
        l_y1_dest = l_y0_dest + l_img_comp_dest->h;

        /*if (i == 0) {
        fprintf(stdout, "DEST: l_x0_dest=%d, l_x1_dest=%d, l_y0_dest=%d, l_y1_dest=%d (%d)\n",
                        l_x0_dest, l_x1_dest, l_y0_dest, l_y1_dest, l_img_comp_dest->factor );
        }*/

        /*-----*/
        /* Compute the area (l_offset_x0_src, l_offset_y0_src, l_offset_x1_src, l_offset_y1_src)
         * of the input buffer (decoded tile component) which will be move
         * in the output buffer. Compute the area of the output buffer (l_start_x_dest,
         * l_start_y_dest, l_width_dest, l_height_dest)  which will be modified
         * by this input area.
         * */
        assert(res_x0 >= 0);
        assert(res_x1 >= 0);
        if (l_x0_dest < (OPJ_UINT32)res_x0) {
            l_start_x_dest = (OPJ_UINT32)res_x0 - l_x0_dest;
            l_offset_x0_src = 0;

            if (l_x1_dest >= (OPJ_UINT32)res_x1) {
                l_width_dest = l_width_src;
                l_offset_x1_src = 0;
            } else {
                l_width_dest = l_x1_dest - (OPJ_UINT32)res_x0 ;
                l_offset_x1_src = (OPJ_INT32)(l_width_src - l_width_dest);
            }
        } else {
            l_start_x_dest = 0U;
            l_offset_x0_src = (OPJ_INT32)l_x0_dest - res_x0;

            if (l_x1_dest >= (OPJ_UINT32)res_x1) {
                l_width_dest = l_width_src - (OPJ_UINT32)l_offset_x0_src;
                l_offset_x1_src = 0;
            } else {
                l_width_dest = l_img_comp_dest->w ;
                l_offset_x1_src = res_x1 - (OPJ_INT32)l_x1_dest;
            }
        }

        if (l_y0_dest < (OPJ_UINT32)res_y0) {
            l_start_y_dest = (OPJ_UINT32)res_y0 - l_y0_dest;
            l_offset_y0_src = 0;

            if (l_y1_dest >= (OPJ_UINT32)res_y1) {
                l_height_dest = l_height_src;
                l_offset_y1_src = 0;
            } else {
                l_height_dest = l_y1_dest - (OPJ_UINT32)res_y0 ;
                l_offset_y1_src = (OPJ_INT32)(l_height_src - l_height_dest);
            }
        } else {
            l_start_y_dest = 0U;
            l_offset_y0_src = (OPJ_INT32)l_y0_dest - res_y0;

            if (l_y1_dest >= (OPJ_UINT32)res_y1) {
                l_height_dest = l_height_src - (OPJ_UINT32)l_offset_y0_src;
                l_offset_y1_src = 0;
            } else {
                l_height_dest = l_img_comp_dest->h ;
                l_offset_y1_src = res_y1 - (OPJ_INT32)l_y1_dest;
            }
        }

        if ((l_offset_x0_src < 0) || (l_offset_y0_src < 0) || (l_offset_x1_src < 0) ||
                (l_offset_y1_src < 0)) {
            return OPJ_FALSE;
        }
        /* testcase 2977.pdf.asan.67.2198 */
        if ((OPJ_INT32)l_width_dest < 0 || (OPJ_INT32)l_height_dest < 0) {
            return OPJ_FALSE;
        }
        /*-----*/

        /* Compute the input buffer offset */
        l_start_offset_src = (OPJ_SIZE_T)l_offset_x0_src + (OPJ_SIZE_T)l_offset_y0_src
                             * (OPJ_SIZE_T)src_data_stride;

        /* Compute the output buffer offset */
        l_start_offset_dest = (OPJ_SIZE_T)l_start_x_dest + (OPJ_SIZE_T)l_start_y_dest
                              * (OPJ_SIZE_T)l_img_comp_dest->w;

        /* Allocate output component buffer if necessary */
        if (l_img_comp_dest->data == NULL &&
                l_start_offset_src == 0 && l_start_offset_dest == 0 &&
                src_data_stride == l_img_comp_dest->w &&
                l_width_dest == l_img_comp_dest->w &&
                l_height_dest == l_img_comp_dest->h) {
            /* If the final image matches the tile buffer, then borrow it */
            /* directly to save a copy */
            if (p_tcd->whole_tile_decoding) {
                l_img_comp_dest->data = l_tilec->data;
                l_tilec->data = NULL;
            } else {
                l_img_comp_dest->data = l_tilec->data_win;
                l_tilec->data_win = NULL;
            }
            continue;
        } else if (l_img_comp_dest->data == NULL) {
            OPJ_SIZE_T l_width = l_img_comp_dest->w;
            OPJ_SIZE_T l_height = l_img_comp_dest->h;

            if ((l_height == 0U) || (l_width > (SIZE_MAX / l_height)) ||
                    l_width * l_height > SIZE_MAX / sizeof(OPJ_INT32)) {
                /* would overflow */
                return OPJ_FALSE;
            }
            l_img_comp_dest->data = (OPJ_INT32*) opj_image_data_alloc(l_width * l_height *
                                    sizeof(OPJ_INT32));
            if (! l_img_comp_dest->data) {
                return OPJ_FALSE;
            }

            if (l_img_comp_dest->w != l_width_dest ||
                    l_img_comp_dest->h != l_height_dest) {
                memset(l_img_comp_dest->data, 0,
                       (OPJ_SIZE_T)l_img_comp_dest->w * l_img_comp_dest->h * sizeof(OPJ_INT32));
            }
        }

        /* Move the output buffer to the first place where we will write*/
        l_dest_ptr = l_img_comp_dest->data + l_start_offset_dest;

        {
            const OPJ_INT32 * l_src_ptr = p_src_data;
            l_src_ptr += l_start_offset_src;

            for (j = 0; j < l_height_dest; ++j) {
                memcpy(l_dest_ptr, l_src_ptr, l_width_dest * sizeof(OPJ_INT32));
                l_dest_ptr += l_img_comp_dest->w;
                l_src_ptr += src_data_stride;
            }
        }


    }

    return OPJ_TRUE;
}