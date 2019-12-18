#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sz; int /*<<< orphan*/  surfaces; } ;
struct TYPE_6__ {int /*<<< orphan*/  sz; int /*<<< orphan*/  surfaces; } ;
struct deint_data {TYPE_1__ forward_refs; TYPE_2__ backward_refs; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_forward_references; int /*<<< orphan*/  num_backward_references; int /*<<< orphan*/  forward_references; int /*<<< orphan*/  backward_references; } ;
typedef  TYPE_3__ VAProcPipelineParameterBuffer ;

/* Variables and functions */

__attribute__((used)) static void
Deinterlace_UpdatePipelineParams
(void * p_data, VAProcPipelineParameterBuffer * pipeline_param)
{
    struct deint_data *const    p_deint_data = p_data;

    pipeline_param->backward_references = p_deint_data->backward_refs.surfaces;
    pipeline_param->forward_references = p_deint_data->forward_refs.surfaces;
    pipeline_param->num_backward_references = p_deint_data->backward_refs.sz;
    pipeline_param->num_forward_references = p_deint_data->forward_refs.sz;
}