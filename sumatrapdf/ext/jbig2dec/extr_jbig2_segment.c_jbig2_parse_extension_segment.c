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
typedef  int uint32_t ;
struct TYPE_3__ {int data_length; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ Jbig2Segment ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_FATAL ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_INFO ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_WARNING ; 
 int jbig2_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int jbig2_get_uint32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
jbig2_parse_extension_segment(Jbig2Ctx *ctx, Jbig2Segment *segment, const uint8_t *segment_data)
{
    uint32_t type;
    bool reserved;
    bool necessary;

    if (segment->data_length < 4)
        return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number, "segment too short");

    type = jbig2_get_uint32(segment_data);
    reserved = type & 0x20000000;
    /* Not implemented since this bit
    is only needed by encoders.
    dependent = type & 0x40000000;
    */
    necessary = type & 0x80000000;

    if (necessary && !reserved) {
        jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number, "extension segment is marked 'necessary' but not 'reserved' contrary to spec");
    }

    switch (type) {
    case 0x20000000:
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "ignoring ASCII comment");
        break;
    case 0x20000002:
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "ignoring UCS-2 comment");
        break;
    default:
        if (necessary) {
            return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number, "unhandled necessary extension segment type 0x%08x", type);
        } else {
            jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number, "unhandled non-necessary extension segment, skipping");
        }
    }

    return 0;
}