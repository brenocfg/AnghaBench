#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
typedef  int int8_t ;
struct TYPE_36__ {int* gbat; int MMR; int GBTEMPLATE; int /*<<< orphan*/  USESKIP; scalar_t__ TPGDON; } ;
struct TYPE_35__ {int stride; int height; } ;
struct TYPE_34__ {int data_length; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ Jbig2Segment ;
typedef  TYPE_2__ Jbig2Image ;
typedef  TYPE_3__ Jbig2GenericRegionParams ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;
typedef  int /*<<< orphan*/  Jbig2ArithState ;
typedef  int /*<<< orphan*/  Jbig2ArithCx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_DEBUG ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_FATAL ; 
 int jbig2_decode_generic_region_TPGDON (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__ const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int jbig2_decode_generic_template0 (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__ const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int jbig2_decode_generic_template0_unopt (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__ const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int jbig2_decode_generic_template1 (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__ const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int jbig2_decode_generic_template1_unopt (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__ const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int jbig2_decode_generic_template2 (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__ const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int jbig2_decode_generic_template2_unopt (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__ const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int jbig2_decode_generic_template3 (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__ const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int jbig2_decode_generic_template3_unopt (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__ const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int jbig2_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 

int
jbig2_decode_generic_region(Jbig2Ctx *ctx,
                            Jbig2Segment *segment, const Jbig2GenericRegionParams *params, Jbig2ArithState *as, Jbig2Image *image, Jbig2ArithCx *GB_stats)
{
    const int8_t *gbat = params->gbat;

    if (image->stride * image->height > (1 << 26) && segment->data_length < image->stride * image->height / (1 << 16)) {
        return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number,
                           "region is far larger than data provided (%d << %d), aborting to prevent DOS", segment->data_length, image->stride * image->height);
    }

    if (!params->MMR && params->TPGDON)
        return jbig2_decode_generic_region_TPGDON(ctx, segment, params, as, image, GB_stats);

    if (!params->MMR && params->GBTEMPLATE == 0) {
        if (!params->USESKIP && gbat[0] == +3 && gbat[1] == -1 && gbat[2] == -3 && gbat[3] == -1 && gbat[4] == +2 && gbat[5] == -2 && gbat[6] == -2 && gbat[7] == -2)
            return jbig2_decode_generic_template0(ctx, segment, params, as, image, GB_stats);
        else
            return jbig2_decode_generic_template0_unopt(ctx, segment, params, as, image, GB_stats);
    } else if (!params->MMR && params->GBTEMPLATE == 1) {
        if (!params->USESKIP && gbat[0] == +3 && gbat[1] == -1)
            return jbig2_decode_generic_template1(ctx, segment, params, as, image, GB_stats);
        else
            return jbig2_decode_generic_template1_unopt(ctx, segment, params, as, image, GB_stats);
    }
    else if (!params->MMR && params->GBTEMPLATE == 2) {
        if (!params->USESKIP && gbat[0] == 2 && gbat[1] == -1)
            return jbig2_decode_generic_template2(ctx, segment, params, as, image, GB_stats);
        else
            return jbig2_decode_generic_template2_unopt(ctx, segment, params, as, image, GB_stats);
    } else if (!params->MMR && params->GBTEMPLATE == 3) {
        if (!params->USESKIP && gbat[0] == 2 && gbat[1] == -1)
            return jbig2_decode_generic_template3(ctx, segment, params, as, image, GB_stats);
        else
            return jbig2_decode_generic_template3_unopt(ctx, segment, params, as, image, GB_stats);
    }

    {
        int i;

        for (i = 0; i < 8; i++)
            jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, segment->number, "gbat[%d] = %d", i, params->gbat[i]);
    }

    return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number, "unsupported generic region (MMR=%d, GBTEMPLATE=%d)", params->MMR, params->GBTEMPLATE);
}