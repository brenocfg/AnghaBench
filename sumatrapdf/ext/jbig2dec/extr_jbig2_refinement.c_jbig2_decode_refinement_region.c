#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ GRTEMPLATE; scalar_t__ TPGRON; int /*<<< orphan*/  GRREFERENCEDY; int /*<<< orphan*/  GRREFERENCEDX; } ;
struct TYPE_10__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ Jbig2Segment ;
typedef  TYPE_2__ Jbig2RefinementRegionParams ;
typedef  int /*<<< orphan*/  Jbig2Image ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;
typedef  int /*<<< orphan*/  Jbig2ArithState ;
typedef  int /*<<< orphan*/  Jbig2ArithCx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_DEBUG ; 
 int jbig2_decode_refinement_TPGRON (int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int jbig2_decode_refinement_template0_unopt (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int jbig2_decode_refinement_template1_unopt (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbig2_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int
jbig2_decode_refinement_region(Jbig2Ctx *ctx,
                               Jbig2Segment *segment,
                               const Jbig2RefinementRegionParams *params, Jbig2ArithState *as, Jbig2Image *image, Jbig2ArithCx *GR_stats)
{
    jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, segment->number,
                "decoding generic refinement region with offset %d,%x, GRTEMPLATE=%d, TPGRON=%d",
                params->GRREFERENCEDX, params->GRREFERENCEDY, params->GRTEMPLATE, params->TPGRON);

    if (params->TPGRON)
        return jbig2_decode_refinement_TPGRON(ctx, params, as, image, GR_stats);

    if (params->GRTEMPLATE)
        return jbig2_decode_refinement_template1_unopt(ctx, segment, params, as, image, GR_stats);
    else
        return jbig2_decode_refinement_template0_unopt(ctx, segment, params, as, image, GR_stats);
}