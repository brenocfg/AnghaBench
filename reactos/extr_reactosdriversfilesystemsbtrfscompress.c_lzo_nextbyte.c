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
struct TYPE_3__ {size_t inpos; size_t inlen; int /*<<< orphan*/ * in; int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ lzo_stream ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static UINT8 lzo_nextbyte(lzo_stream* stream) {
    UINT8 c;

    if (stream->inpos >= stream->inlen) {
        stream->error = TRUE;
        return 0;
    }

    c = stream->in[stream->inpos];
    stream->inpos++;

    return c;
}