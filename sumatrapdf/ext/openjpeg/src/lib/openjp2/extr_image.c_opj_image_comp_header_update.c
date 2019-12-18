#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct opj_cp {scalar_t__ tx0; scalar_t__ ty0; unsigned int tw; unsigned int tdx; unsigned int th; unsigned int tdy; } ;
struct TYPE_4__ {scalar_t__ numcomps; TYPE_2__* comps; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; int /*<<< orphan*/  y0; int /*<<< orphan*/  x0; } ;
typedef  TYPE_1__ opj_image_t ;
struct TYPE_5__ {scalar_t__ y0; scalar_t__ x0; scalar_t__ h; scalar_t__ w; int /*<<< orphan*/  factor; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
typedef  TYPE_2__ opj_image_comp_t ;
typedef  scalar_t__ OPJ_UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  opj_uint_adds (scalar_t__,unsigned int) ; 
 scalar_t__ opj_uint_ceildiv (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ opj_uint_ceildivpow2 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ opj_uint_max (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ opj_uint_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void opj_image_comp_header_update(opj_image_t * p_image_header,
                                  const struct opj_cp * p_cp)
{
    OPJ_UINT32 i, l_width, l_height;
    OPJ_UINT32 l_x0, l_y0, l_x1, l_y1;
    OPJ_UINT32 l_comp_x0, l_comp_y0, l_comp_x1, l_comp_y1;
    opj_image_comp_t* l_img_comp = NULL;

    l_x0 = opj_uint_max(p_cp->tx0, p_image_header->x0);
    l_y0 = opj_uint_max(p_cp->ty0, p_image_header->y0);
    l_x1 = p_cp->tx0 + (p_cp->tw - 1U) *
           p_cp->tdx; /* validity of p_cp members used here checked in opj_j2k_read_siz. Can't overflow. */
    l_y1 = p_cp->ty0 + (p_cp->th - 1U) * p_cp->tdy; /* can't overflow */
    l_x1 = opj_uint_min(opj_uint_adds(l_x1, p_cp->tdx),
                        p_image_header->x1); /* use add saturated to prevent overflow */
    l_y1 = opj_uint_min(opj_uint_adds(l_y1, p_cp->tdy),
                        p_image_header->y1); /* use add saturated to prevent overflow */

    l_img_comp = p_image_header->comps;
    for (i = 0; i < p_image_header->numcomps; ++i) {
        l_comp_x0 = opj_uint_ceildiv(l_x0, l_img_comp->dx);
        l_comp_y0 = opj_uint_ceildiv(l_y0, l_img_comp->dy);
        l_comp_x1 = opj_uint_ceildiv(l_x1, l_img_comp->dx);
        l_comp_y1 = opj_uint_ceildiv(l_y1, l_img_comp->dy);
        l_width   = opj_uint_ceildivpow2(l_comp_x1 - l_comp_x0, l_img_comp->factor);
        l_height  = opj_uint_ceildivpow2(l_comp_y1 - l_comp_y0, l_img_comp->factor);
        l_img_comp->w = l_width;
        l_img_comp->h = l_height;
        l_img_comp->x0 = l_comp_x0;
        l_img_comp->y0 = l_comp_y0;
        ++l_img_comp;
    }
}