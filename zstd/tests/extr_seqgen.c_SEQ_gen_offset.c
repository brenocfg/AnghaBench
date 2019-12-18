#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; int pos; scalar_t__ dst; } ;
struct TYPE_5__ {int state; unsigned int bytesLeft; int /*<<< orphan*/  xxh; int /*<<< orphan*/  saved; int /*<<< orphan*/  seed; } ;
typedef  TYPE_1__ SEQ_stream ;
typedef  TYPE_2__ SEQ_outBuffer ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 unsigned int MIN (unsigned int,size_t) ; 
 int SEQ_randByte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XXH64_update (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int) ; 
 size_t kMatchBytes ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static size_t SEQ_gen_offset(SEQ_stream* stream, unsigned value, SEQ_outBuffer* out)
{
    typedef enum {
        of_start = 0,
        of_run_bytes,
        of_offset,
        of_run_match,
    } of_state;
    BYTE* const ostart = (BYTE*)out->dst;
    BYTE* const oend = ostart + out->size;
    BYTE* op = ostart + out->pos;

    switch ((of_state)stream->state) {
    case of_start:
        stream->state = of_run_bytes;
        stream->saved = stream->seed;
        stream->bytesLeft = MIN(value, kMatchBytes);
    /* fall-through */
    case of_run_bytes: {
        while (stream->bytesLeft > 0 && op < oend) {
            *op++ = SEQ_randByte(&stream->seed) | 0x80;
            --stream->bytesLeft;
        }
        if (stream->bytesLeft > 0)
            break;
        /* State transition */
        stream->state = of_offset;
        stream->bytesLeft = value - MIN(value, kMatchBytes);
    }
    /* fall-through */
    case of_offset: {
        /* Copy matchLength + 1 bytes to the output buffer */
        size_t const setLength = MIN(stream->bytesLeft, (size_t)(oend - op));
        if (setLength > 0) {
            memset(op, 0, setLength);
            op += setLength;
            stream->bytesLeft -= setLength;
        }
        if (stream->bytesLeft > 0)
            break;
        /* State transition */
        stream->state = of_run_match;
        stream->bytesLeft = MIN(value, kMatchBytes);
    }
    /* fall-through */
    case of_run_match: {
        while (stream->bytesLeft > 0 && op < oend) {
            *op++ = SEQ_randByte(&stream->saved) | 0x80;
            --stream->bytesLeft;
        }
        if (stream->bytesLeft > 0)
            break;
    }
    /* fall-through */
    default:
        stream->state = 0;
        stream->bytesLeft = 0;
        break;
    }
    XXH64_update(&stream->xxh, ostart + out->pos, (op - ostart) - out->pos);
    out->pos = op - ostart;
    return stream->bytesLeft;
}