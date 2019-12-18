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
typedef  int /*<<< orphan*/  ar_stream_tell_fn ;
typedef  int /*<<< orphan*/  ar_stream_seek_fn ;
typedef  int /*<<< orphan*/  ar_stream_read_fn ;
typedef  int /*<<< orphan*/  (* ar_stream_close_fn ) (void*) ;
struct TYPE_4__ {int /*<<< orphan*/  tell; int /*<<< orphan*/  seek; int /*<<< orphan*/  read; int /*<<< orphan*/  (* close ) (void*) ;void* data; } ;
typedef  TYPE_1__ ar_stream ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

ar_stream *ar_open_stream(void *data, ar_stream_close_fn close, ar_stream_read_fn read, ar_stream_seek_fn seek, ar_stream_tell_fn tell)
{
    ar_stream *stream = malloc(sizeof(ar_stream));
    if (!stream) {
        close(data);
        return NULL;
    }
    stream->data = data;
    stream->close = close;
    stream->read = read;
    stream->seek = seek;
    stream->tell = tell;
    return stream;
}