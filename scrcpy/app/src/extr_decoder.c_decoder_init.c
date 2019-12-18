#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct video_buffer {int dummy; } ;
struct decoder {struct video_buffer* video_buffer; } ;

/* Variables and functions */

void
decoder_init(struct decoder *decoder, struct video_buffer *vb) {
    decoder->video_buffer = vb;
}