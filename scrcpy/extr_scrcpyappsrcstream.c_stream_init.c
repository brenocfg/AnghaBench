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
struct stream {struct recorder* recorder; struct decoder* decoder; int /*<<< orphan*/  socket; } ;
struct recorder {int dummy; } ;
struct decoder {int dummy; } ;
typedef  int /*<<< orphan*/  socket_t ;

/* Variables and functions */

void
stream_init(struct stream *stream, socket_t socket,
            struct decoder *decoder, struct recorder *recorder) {
    stream->socket = socket;
    stream->decoder = decoder,
    stream->recorder = recorder;
}