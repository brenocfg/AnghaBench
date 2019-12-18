#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ i_desc_bytes; scalar_t__ i_bytes; scalar_t__ i_samples; scalar_t__ i_frames; } ;
typedef  TYPE_1__ frame_span_t ;

/* Variables and functions */

__attribute__((used)) static inline void FrameSpanAddSpan( frame_span_t *span1, frame_span_t *span2 )
{
    span1->i_frames += span2->i_frames;
    span1->i_samples += span2->i_samples;
    span1->i_bytes += span2->i_bytes;
    span1->i_desc_bytes += span2->i_desc_bytes;
}