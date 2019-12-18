#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct adjust_params {TYPE_2__* sigma; } ;
struct adjust_data {int num_available_modes; struct adjust_params params; } ;
struct TYPE_17__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_15__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  dpy; } ;
struct TYPE_18__ {TYPE_1__ va; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_19__ {scalar_t__ attrib; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ VAProcFilterParameterBufferColorBalance ;
struct TYPE_20__ {scalar_t__ type; int /*<<< orphan*/  range; } ;
typedef  TYPE_6__ VAProcFilterCapColorBalance ;
struct TYPE_21__ {int /*<<< orphan*/  max_value; int /*<<< orphan*/  min_value; } ;
struct TYPE_16__ {int is_available; int /*<<< orphan*/  drv_value; int /*<<< orphan*/  drv_range; } ;

/* Variables and functions */
 float GET_DRV_SIGMA (float,TYPE_8__,int /*<<< orphan*/ ) ; 
 unsigned int NUM_ADJUST_MODES ; 
 int VAProcColorBalanceCount ; 
 int /*<<< orphan*/  VAProcFilterColorBalance ; 
 float VLC_CLIP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_3__*) ; 
 int VLC_SUCCESS ; 
 float adapt_adjust_sigma (int /*<<< orphan*/ ,float,TYPE_8__*) ; 
 int /*<<< orphan*/ * adjust_params_names ; 
 TYPE_5__* calloc (int,int) ; 
 scalar_t__* va_adjust_modes ; 
 int /*<<< orphan*/  var_InheritFloat (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* vlc_adjust_sigma_ranges ; 
 int /*<<< orphan*/  vlc_atomic_init_float (int /*<<< orphan*/ *,float const) ; 
 scalar_t__ vlc_vaapi_QueryVideoProcFilterCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,unsigned int*) ; 

__attribute__((used)) static int
OpenAdjust_InitFilterParams(filter_t * filter, void * p_data,
                            void ** pp_va_params,
                            uint32_t * p_va_param_sz,
                            uint32_t * p_num_va_params)
{
    struct adjust_data *const   p_adjust_data = p_data;
    struct adjust_params *const p_adjust_params = &p_adjust_data->params;
    filter_sys_t *const         filter_sys = filter->p_sys;
    VAProcFilterCapColorBalance caps[VAProcColorBalanceCount];
    unsigned int                num_caps = VAProcColorBalanceCount;

    if (vlc_vaapi_QueryVideoProcFilterCaps(VLC_OBJECT(filter),
                                           filter_sys->va.dpy,
                                           filter_sys->va.ctx,
                                           VAProcFilterColorBalance,
                                           caps, &num_caps))
        return VLC_EGENERIC;

    for (unsigned int i = 0; i < num_caps; ++i)
    {
        unsigned int    j;

        for (j = 0; j < num_caps; ++j)
            if (caps[j].type == va_adjust_modes[i])
            {
                float   vlc_sigma =
                    VLC_CLIP(var_InheritFloat(filter, adjust_params_names[i]),
                             vlc_adjust_sigma_ranges[i].min_value,
                             vlc_adjust_sigma_ranges[i].max_value);
                vlc_sigma =
                    adapt_adjust_sigma(adjust_params_names[i],
                                       vlc_sigma, vlc_adjust_sigma_ranges + i);

                p_adjust_params->sigma[i].drv_range = caps[j].range;
                p_adjust_params->sigma[i].is_available = true;
                ++p_adjust_data->num_available_modes;

                float const     drv_sigma =
                    GET_DRV_SIGMA(vlc_sigma, vlc_adjust_sigma_ranges[i],
                                  p_adjust_params->sigma[i].drv_range);

                vlc_atomic_init_float(&p_adjust_params->sigma[i].drv_value,
                                      drv_sigma);
                break;
            }
    }

    VAProcFilterParameterBufferColorBalance *   p_va_params;

    *p_va_param_sz = sizeof(typeof(*p_va_params));
    *p_num_va_params = p_adjust_data->num_available_modes;

    p_va_params = calloc(*p_num_va_params, *p_va_param_sz);
    if (!p_va_params)
        return VLC_ENOMEM;

    unsigned int i = 0;
    for (unsigned int j = 0; j < NUM_ADJUST_MODES; ++j)
        if (p_adjust_params->sigma[j].is_available)
        {
            p_va_params[i].type = VAProcFilterColorBalance;
            p_va_params[i++].attrib = va_adjust_modes[j];
        }

    *pp_va_params = p_va_params;

    return VLC_SUCCESS;
}