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
struct TYPE_3__ {size_t outpos; int outlen; int /*<<< orphan*/ * out; void* error; } ;
typedef  TYPE_1__ lzo_stream ;
typedef  size_t UINT32 ;

/* Variables and functions */
 void* TRUE ; 

__attribute__((used)) static void lzo_copyback(lzo_stream* stream, UINT32 back, int len) {
    if (stream->outpos < back) {
        stream->error = TRUE;
        return;
    }

    if (stream->outpos + len > stream->outlen) {
        stream->error = TRUE;
        return;
    }

    do {
        stream->out[stream->outpos] = stream->out[stream->outpos - back];
        stream->outpos++;
        len--;
    } while (len > 0);
}