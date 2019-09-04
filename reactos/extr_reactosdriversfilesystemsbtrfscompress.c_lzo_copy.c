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
struct TYPE_3__ {int inpos; int inlen; int outpos; int outlen; int /*<<< orphan*/ * in; int /*<<< orphan*/ * out; void* error; } ;
typedef  TYPE_1__ lzo_stream ;

/* Variables and functions */
 void* TRUE ; 

__attribute__((used)) static void lzo_copy(lzo_stream* stream, int len) {
    if (stream->inpos + len > stream->inlen) {
        stream->error = TRUE;
        return;
    }

    if (stream->outpos + len > stream->outlen) {
        stream->error = TRUE;
        return;
    }

    do {
        stream->out[stream->outpos] = stream->in[stream->inpos];
        stream->inpos++;
        stream->outpos++;
        len--;
    } while (len > 0);
}