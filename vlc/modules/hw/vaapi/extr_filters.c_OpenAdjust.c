#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct adjust_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pf_video_filter; } ;
typedef  TYPE_1__ filter_t ;
typedef  int /*<<< orphan*/  VAProcPipelineCaps ;

/* Variables and functions */
 int /*<<< orphan*/  Adjust ; 
 int /*<<< orphan*/  FilterCallback ; 
 unsigned int NUM_ADJUST_MODES ; 
 scalar_t__ Open (TYPE_1__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct adjust_data* const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenAdjust_InitFilterParams ; 
 int /*<<< orphan*/  VAProcFilterColorBalance ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int VLC_VAR_DOINHERIT ; 
 int VLC_VAR_FLOAT ; 
 int VLC_VAR_ISCOMMAND ; 
 int /*<<< orphan*/ * adjust_params_names ; 
 struct adjust_data* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct adjust_data* const) ; 
 int /*<<< orphan*/  var_AddCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adjust_data* const) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  var_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
OpenAdjust(vlc_object_t * obj)
{
    VAProcPipelineCaps          pipeline_caps;
    filter_t *const             filter = (filter_t *)obj;
    struct adjust_data *const   p_data = calloc(1, sizeof(*p_data));
    if (!p_data)
        return VLC_ENOMEM;

    for (unsigned int i = 0; i < NUM_ADJUST_MODES; ++i)
        var_Create(obj, adjust_params_names[i],
                   VLC_VAR_FLOAT | VLC_VAR_DOINHERIT | VLC_VAR_ISCOMMAND);

    if (Open(filter, VAProcFilterColorBalance, &pipeline_caps, p_data,
             OpenAdjust_InitFilterParams, NULL))
        goto error;

    for (unsigned int i = 0; i < NUM_ADJUST_MODES; ++i)
        var_AddCallback(obj, adjust_params_names[i], FilterCallback, p_data);

    filter->pf_video_filter = Adjust;

    return VLC_SUCCESS;

error:
    for (unsigned int i = 0; i < NUM_ADJUST_MODES; ++i)
        var_Destroy(obj, adjust_params_names[i]);
    free(p_data);
    return VLC_EGENERIC;
}