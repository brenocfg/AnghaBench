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
struct stream {scalar_t__ decoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  decoder_interrupt (scalar_t__) ; 

void
stream_stop(struct stream *stream) {
    if (stream->decoder) {
        decoder_interrupt(stream->decoder);
    }
}