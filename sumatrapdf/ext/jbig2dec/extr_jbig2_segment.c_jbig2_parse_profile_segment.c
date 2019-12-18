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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int data_length; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ Jbig2Segment ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_FATAL ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_INFO ; 
 int jbig2_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ jbig2_get_uint32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
jbig2_parse_profile_segment(Jbig2Ctx *ctx, Jbig2Segment *segment, const uint8_t *segment_data)
{
    uint32_t profiles;
    uint32_t i;
    uint32_t profile;
    int index;
    const char *requirements;
    const char *generic_region;
    const char *refinement_region;
    const char *halftone_region;
    const char *numerical_data;

    if (segment->data_length < 4)
        return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number, "Segment too short");
    index = 0;

    profiles = jbig2_get_uint32(&segment_data[index]);
    index += 4;

    for (i = 0; i < profiles; i++) {
        if (segment->data_length - index < 4)
            return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number, "segment too short to store profile");

        profile = jbig2_get_uint32(&segment_data[index]);
        index += 4;

        switch (profile) {
        case 0x00000001:
            requirements = "All JBIG2 capabilities";
            generic_region = "No restriction";
            refinement_region = "No restriction";
            halftone_region = "No restriction";
            numerical_data = "No restriction";
            break;
        case 0x00000002:
            requirements = "Maximum compression";
            generic_region = "Arithmetic only; any template used";
            refinement_region = "No restriction";
            halftone_region = "No restriction";
            numerical_data = "Arithmetic only";
            break;
        case 0x00000003:
            requirements = "Medium complexity and medium compression";
            generic_region = "Arithmetic only; only 10-pixel and 13-pixel templates";
            refinement_region = "10-pixel template only";
            halftone_region = "No skip mask used";
            numerical_data = "Arithmetic only";
            break;
        case 0x00000004:
            requirements = "Low complexity with progressive lossless capability";
            generic_region = "MMR only";
            refinement_region = "10-pixel template only";
            halftone_region = "No skip mask used";
            numerical_data = "Huffman only";
            break;
        case 0x00000005:
            requirements = "Low complexity";
            generic_region = "MMR only";
            refinement_region = "Not available";
            halftone_region = "No skip mask used";
            numerical_data = "Huffman only";
            break;
        default:
            requirements = "Unknown";
            generic_region = "Unknown";
            refinement_region = "Unknown";
            halftone_region = "Unknown";
            numerical_data = "Unknown";
            break;
        }

        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "Supported profile: 0x%08x", profile);
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "  Requirements: %s", requirements);
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "  Generic region coding: %s", generic_region);
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "  Refinement region coding: %s", refinement_region);
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "  Halftone region coding: %s", halftone_region);
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "  Numerical data: %s", numerical_data);
    }

    return 0;
}