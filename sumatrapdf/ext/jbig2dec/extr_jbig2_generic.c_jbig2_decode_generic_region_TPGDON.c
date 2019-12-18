#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int GBTEMPLATE; } ;
struct TYPE_13__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ Jbig2Segment ;
typedef  int /*<<< orphan*/  Jbig2Image ;
typedef  TYPE_2__ Jbig2GenericRegionParams ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;
typedef  int /*<<< orphan*/  Jbig2ArithState ;
typedef  int /*<<< orphan*/  Jbig2ArithCx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_FATAL ; 
 int jbig2_decode_generic_template0_TPGDON (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int jbig2_decode_generic_template1_TPGDON (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int jbig2_decode_generic_template2_TPGDON (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int jbig2_decode_generic_template3_TPGDON (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int jbig2_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
jbig2_decode_generic_region_TPGDON(Jbig2Ctx *ctx,
                                   Jbig2Segment *segment,
                                   const Jbig2GenericRegionParams *params, Jbig2ArithState *as, Jbig2Image *image, Jbig2ArithCx *GB_stats)
{
    switch (params->GBTEMPLATE) {
    case 0:
        return jbig2_decode_generic_template0_TPGDON(ctx, segment, params, as, image, GB_stats);
    case 1:
        return jbig2_decode_generic_template1_TPGDON(ctx, segment, params, as, image, GB_stats);
    case 2:
        return jbig2_decode_generic_template2_TPGDON(ctx, segment, params, as, image, GB_stats);
    case 3:
        return jbig2_decode_generic_template3_TPGDON(ctx, segment, params, as, image, GB_stats);
    }

    return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number, "unsupported GBTEMPLATE (%d)", params->GBTEMPLATE);
}