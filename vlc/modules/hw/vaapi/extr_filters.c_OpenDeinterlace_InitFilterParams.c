#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct deint_mode {int /*<<< orphan*/  b_double_rate; int /*<<< orphan*/  type; } ;
struct deint_data {int /*<<< orphan*/  b_double_rate; } ;
struct TYPE_11__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_10__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  dpy; } ;
struct TYPE_12__ {TYPE_1__ va; } ;
typedef  TYPE_3__ filter_sys_t ;
struct TYPE_13__ {int /*<<< orphan*/  algorithm; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ VAProcFilterParameterBufferDeinterlacing ;
typedef  int /*<<< orphan*/  VAProcFilterCapDeinterlacing ;

/* Variables and functions */
 int OpenDeinterlace_GetMode (TYPE_2__*,char* const,struct deint_mode*,int /*<<< orphan*/ *,unsigned int) ; 
 int VAProcDeinterlacingCount ; 
 int /*<<< orphan*/  VAProcFilterDeinterlacing ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int VLC_SUCCESS ; 
 TYPE_4__* calloc (int,int) ; 
 int /*<<< orphan*/  free (char* const) ; 
 char* var_InheritString (TYPE_2__*,char*) ; 
 scalar_t__ vlc_vaapi_QueryVideoProcFilterCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,unsigned int*) ; 

__attribute__((used)) static int
OpenDeinterlace_InitFilterParams(filter_t * filter, void * p_data,
                                 void ** pp_va_params,
                                 uint32_t * p_va_param_sz,
                                 uint32_t * p_num_va_params)
{
    struct deint_data *const    p_deint_data = p_data;
    filter_sys_t *const         filter_sys = filter->p_sys;
    VAProcFilterCapDeinterlacing
                                caps[VAProcDeinterlacingCount];
    unsigned int                num_caps = VAProcDeinterlacingCount;

    if (vlc_vaapi_QueryVideoProcFilterCaps(VLC_OBJECT(filter),
                                           filter_sys->va.dpy,
                                           filter_sys->va.buf,
                                           VAProcFilterDeinterlacing,
                                           &caps, &num_caps))
        return VLC_EGENERIC;

    struct deint_mode   deint_mode;
    char *const         psz_deint_mode =
        var_InheritString(filter, "deinterlace-mode");

    int ret = OpenDeinterlace_GetMode(filter, psz_deint_mode,
                                      &deint_mode, caps, num_caps);
    free(psz_deint_mode);
    if (ret)
        return VLC_EGENERIC;

    VAProcFilterParameterBufferDeinterlacing *  p_va_param;

    *p_va_param_sz = sizeof(*p_va_param);
    *p_num_va_params = 1;

    p_va_param = calloc(1, sizeof(*p_va_param));
    if (!p_va_param)
        return VLC_ENOMEM;

    p_va_param->type = VAProcFilterDeinterlacing;
    p_va_param->algorithm = deint_mode.type;
    *pp_va_params = p_va_param;

    p_deint_data->b_double_rate = deint_mode.b_double_rate;

    return VLC_SUCCESS;
}