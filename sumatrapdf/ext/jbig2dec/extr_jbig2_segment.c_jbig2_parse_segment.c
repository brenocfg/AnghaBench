#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_31__ {int /*<<< orphan*/  state; } ;
struct TYPE_30__ {int flags; int /*<<< orphan*/  number; int /*<<< orphan*/  data_length; } ;
typedef  TYPE_1__ Jbig2Segment ;
typedef  TYPE_2__ Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_FILE_EOF ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_FATAL ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_INFO ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_WARNING ; 
 int jbig2_end_of_page (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int jbig2_end_of_stripe (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int jbig2_error (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int jbig2_halftone_region (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int jbig2_immediate_generic_region (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int jbig2_page_info (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int jbig2_parse_extension_segment (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int jbig2_parse_profile_segment (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int jbig2_pattern_dictionary (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int jbig2_refinement_region (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int jbig2_symbol_dictionary (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int jbig2_table (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int jbig2_text_region (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 

int
jbig2_parse_segment(Jbig2Ctx *ctx, Jbig2Segment *segment, const uint8_t *segment_data)
{
    jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number,
                "segment %d, flags=%x, type=%d, data_length=%d", segment->number, segment->flags, segment->flags & 63, segment->data_length);
    switch (segment->flags & 63) {
    case 0:
        return jbig2_symbol_dictionary(ctx, segment, segment_data);
    case 4:                    /* intermediate text region */
    case 6:                    /* immediate text region */
    case 7:                    /* immediate lossless text region */
        return jbig2_text_region(ctx, segment, segment_data);
    case 16:
        return jbig2_pattern_dictionary(ctx, segment, segment_data);
    case 20:                   /* intermediate halftone region */
    case 22:                   /* immediate halftone region */
    case 23:                   /* immediate lossless halftone region */
        return jbig2_halftone_region(ctx, segment, segment_data);
    case 36:
        return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number, "unhandled segment type 'intermediate generic region' (NYI)");
    case 38:                   /* immediate generic region */
    case 39:                   /* immediate lossless generic region */
        return jbig2_immediate_generic_region(ctx, segment, segment_data);
    case 40:                   /* intermediate generic refinement region */
    case 42:                   /* immediate generic refinement region */
    case 43:                   /* immediate lossless generic refinement region */
        return jbig2_refinement_region(ctx, segment, segment_data);
    case 48:
        return jbig2_page_info(ctx, segment, segment_data);
    case 49:
        return jbig2_end_of_page(ctx, segment, segment_data);
    case 50:
        return jbig2_end_of_stripe(ctx, segment, segment_data);
    case 51:
        ctx->state = JBIG2_FILE_EOF;
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "end of file");
        break;
    case 52:
        return jbig2_parse_profile_segment(ctx, segment, segment_data);
    case 53:                   /* user-supplied huffman table */
        return jbig2_table(ctx, segment, segment_data);
    case 54:
        return jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number, "unhandled segment type 'color palette' (NYI)");
    case 62:
        return jbig2_parse_extension_segment(ctx, segment, segment_data);
    default:
        jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number, "unknown segment type %d", segment->flags & 63);
    }
    return 0;
}