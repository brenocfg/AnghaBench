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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct range {int dummy; } ;
struct TYPE_4__ {char const* psz_name; struct range const* p_vlc_range; } ;
struct basic_filter_data {TYPE_1__ sigma; int /*<<< orphan*/  filter_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  pf_video_filter; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_2__ filter_t ;
typedef  int /*<<< orphan*/  VAProcPipelineCaps ;
typedef  int /*<<< orphan*/  VAProcFilterType ;

/* Variables and functions */
 int /*<<< orphan*/  BasicFilter ; 
 int /*<<< orphan*/  FilterCallback ; 
 scalar_t__ Open (TYPE_2__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct basic_filter_data* const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenBasicFilter_InitFilterParams ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int VLC_VAR_DOINHERIT ; 
 int VLC_VAR_FLOAT ; 
 int VLC_VAR_ISCOMMAND ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct basic_filter_data* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct basic_filter_data* const) ; 
 int /*<<< orphan*/  var_AddCallback (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct basic_filter_data* const) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  var_Destroy (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
OpenBasicFilter(vlc_object_t * obj, VAProcFilterType filter_type,
                const char *psz_sigma_name, struct range const *p_vlc_range)
{
    VAProcPipelineCaps                  pipeline_caps;
    filter_t *const                     filter = (filter_t *)obj;
    assert(filter->psz_name);
    struct basic_filter_data *const     p_data = calloc(1, sizeof(*p_data));
    if (!p_data)
        return VLC_ENOMEM;

    p_data->filter_type = filter_type;
    p_data->sigma.psz_name = psz_sigma_name;
    p_data->sigma.p_vlc_range = p_vlc_range;

    var_Create(obj, p_data->sigma.psz_name,
               VLC_VAR_FLOAT | VLC_VAR_DOINHERIT | VLC_VAR_ISCOMMAND);

    if (Open(filter, p_data->filter_type, &pipeline_caps, p_data,
             OpenBasicFilter_InitFilterParams, NULL))
        goto error;

    var_AddCallback(obj, p_data->sigma.psz_name, FilterCallback, p_data);

    filter->pf_video_filter = BasicFilter;

    return VLC_SUCCESS;

error:
    var_Destroy(obj, p_data->sigma.psz_name);
    free(p_data);
    return VLC_EGENERIC;
}