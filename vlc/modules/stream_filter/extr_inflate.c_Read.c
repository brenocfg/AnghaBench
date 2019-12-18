#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_9__ {size_t avail_out; scalar_t__ avail_in; int next_in; void* next_out; } ;
struct TYPE_8__ {int eof; int buffer; TYPE_5__ zstream; } ;
typedef  TYPE_2__ stream_sys_t ;
typedef  int ssize_t ;

/* Variables and functions */
#define  Z_BUF_ERROR 131 
#define  Z_DATA_ERROR 130 
#define  Z_OK 129 
#define  Z_STREAM_END 128 
 int /*<<< orphan*/  Z_SYNC_FLUSH ; 
 int inflate (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,...) ; 
 scalar_t__ unlikely (int) ; 
 int vlc_stream_Read (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static ssize_t Read(stream_t *stream, void *buf, size_t buflen)
{
    stream_sys_t *sys = stream->p_sys;
    ssize_t val;

    if (sys->eof || unlikely(buflen == 0))
        return 0;

    sys->zstream.next_out = buf;
    sys->zstream.avail_out = buflen;

    if (sys->zstream.avail_in == 0)
        sys->zstream.next_in = sys->buffer;

    val = (sys->buffer + sizeof (sys->buffer))
        - (sys->zstream.next_in + sys->zstream.avail_in);

    if (val > 0)
    {   /* Fill input buffer if there is space left */
        val = vlc_stream_Read(stream->s,
                          sys->zstream.next_in + sys->zstream.avail_in, val);
        if (val >= 0)
            sys->zstream.avail_in += val;
    }

    if (sys->zstream.avail_in == 0)
    {
        msg_Err(stream, "unexpected end of stream");
        return 0;
    }

    val = inflate(&sys->zstream, Z_SYNC_FLUSH);
    switch (val)
    {
        case Z_STREAM_END:
            msg_Dbg(stream, "end of stream");
            sys->eof = true;
            /* fall through */
        case Z_OK:
            return buflen - sys->zstream.avail_out;
        case Z_DATA_ERROR:
            msg_Err(stream, "corrupt stream");
            sys->eof = true;
            return -1;
        case Z_BUF_ERROR:
            if (sys->zstream.next_in == sys->buffer)
                break;

            memmove(sys->buffer, sys->zstream.next_in, sys->zstream.avail_in);
            sys->zstream.next_in = sys->buffer;
            return Read(stream, buf, buflen);
    }

    msg_Err(stream, "unhandled decompression error (%zd)", val);
    return -1;
}