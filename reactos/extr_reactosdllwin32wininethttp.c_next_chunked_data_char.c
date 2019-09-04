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
struct TYPE_3__ {char* buf; int /*<<< orphan*/  buf_pos; int /*<<< orphan*/  buf_size; } ;
typedef  TYPE_1__ chunked_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char next_chunked_data_char(chunked_stream_t *stream)
{
    assert(stream->buf_size);

    stream->buf_size--;
    return stream->buf[stream->buf_pos++];
}