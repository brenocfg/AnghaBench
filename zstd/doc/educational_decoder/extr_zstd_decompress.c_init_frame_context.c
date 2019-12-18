#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  istream_t ;
struct TYPE_5__ {int* previous_offsets; int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ frame_context_t ;
typedef  int /*<<< orphan*/  dictionary_t ;

/* Variables and functions */
 int /*<<< orphan*/  frame_context_apply_dict (TYPE_1__* const,int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_frame_header (int /*<<< orphan*/ *,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static void init_frame_context(frame_context_t *const context,
                               istream_t *const in,
                               const dictionary_t *const dict) {
    // Most fields in context are correct when initialized to 0
    memset(context, 0, sizeof(frame_context_t));

    // Parse data from the frame header
    parse_frame_header(&context->header, in);

    // Set up the offset history for the repeat offset commands
    context->previous_offsets[0] = 1;
    context->previous_offsets[1] = 4;
    context->previous_offsets[2] = 8;

    // Apply details from the dict if it exists
    frame_context_apply_dict(context, dict);
}