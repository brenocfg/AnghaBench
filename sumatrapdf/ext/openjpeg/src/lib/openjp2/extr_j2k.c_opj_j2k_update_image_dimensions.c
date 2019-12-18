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
struct TYPE_4__ {scalar_t__ numcomps; scalar_t__ y1; scalar_t__ x1; scalar_t__ y0; scalar_t__ x0; TYPE_2__* comps; } ;
typedef  TYPE_1__ opj_image_t ;
struct TYPE_5__ {scalar_t__ h; scalar_t__ factor; scalar_t__ y0; scalar_t__ w; scalar_t__ x0; scalar_t__ dy; scalar_t__ dx; } ;
typedef  TYPE_2__ opj_image_comp_t ;
typedef  int /*<<< orphan*/  opj_event_mgr_t ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  scalar_t__ OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ opj_int_ceildiv (scalar_t__,scalar_t__) ; 
 scalar_t__ opj_int_ceildivpow2 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static OPJ_BOOL opj_j2k_update_image_dimensions(opj_image_t* p_image,
        opj_event_mgr_t * p_manager)
{
    OPJ_UINT32 it_comp;
    OPJ_INT32 l_comp_x1, l_comp_y1;
    opj_image_comp_t* l_img_comp = NULL;

    l_img_comp = p_image->comps;
    for (it_comp = 0; it_comp < p_image->numcomps; ++it_comp) {
        OPJ_INT32 l_h, l_w;

        l_img_comp->x0 = (OPJ_UINT32)opj_int_ceildiv((OPJ_INT32)p_image->x0,
                         (OPJ_INT32)l_img_comp->dx);
        l_img_comp->y0 = (OPJ_UINT32)opj_int_ceildiv((OPJ_INT32)p_image->y0,
                         (OPJ_INT32)l_img_comp->dy);
        l_comp_x1 = opj_int_ceildiv((OPJ_INT32)p_image->x1, (OPJ_INT32)l_img_comp->dx);
        l_comp_y1 = opj_int_ceildiv((OPJ_INT32)p_image->y1, (OPJ_INT32)l_img_comp->dy);

        l_w = opj_int_ceildivpow2(l_comp_x1, (OPJ_INT32)l_img_comp->factor)
              - opj_int_ceildivpow2((OPJ_INT32)l_img_comp->x0, (OPJ_INT32)l_img_comp->factor);
        if (l_w < 0) {
            opj_event_msg(p_manager, EVT_ERROR,
                          "Size x of the decoded component image is incorrect (comp[%d].w=%d).\n",
                          it_comp, l_w);
            return OPJ_FALSE;
        }
        l_img_comp->w = (OPJ_UINT32)l_w;

        l_h = opj_int_ceildivpow2(l_comp_y1, (OPJ_INT32)l_img_comp->factor)
              - opj_int_ceildivpow2((OPJ_INT32)l_img_comp->y0, (OPJ_INT32)l_img_comp->factor);
        if (l_h < 0) {
            opj_event_msg(p_manager, EVT_ERROR,
                          "Size y of the decoded component image is incorrect (comp[%d].h=%d).\n",
                          it_comp, l_h);
            return OPJ_FALSE;
        }
        l_img_comp->h = (OPJ_UINT32)l_h;

        l_img_comp++;
    }

    return OPJ_TRUE;
}