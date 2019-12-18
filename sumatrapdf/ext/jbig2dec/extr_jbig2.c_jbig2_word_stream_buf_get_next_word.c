#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {size_t size; int* data; } ;
typedef  TYPE_1__ Jbig2WordStreamBuf ;
typedef  int /*<<< orphan*/  Jbig2WordStream ;

/* Variables and functions */

__attribute__((used)) static int
jbig2_word_stream_buf_get_next_word(Jbig2WordStream *self, size_t offset, uint32_t *word)
{
    Jbig2WordStreamBuf *z = (Jbig2WordStreamBuf *) self;
    uint32_t val = 0;
    int ret = 0;

    if (self == NULL || word == NULL)
        return -1;
    if (offset >= z->size) {
        *word = 0;
        return 0;
    }

    if (offset < z->size) {
        val |= z->data[offset] << 24;
        ret++;
    }
    if (offset + 1 < z->size) {
        val |= z->data[offset + 1] << 16;
        ret++;
    }
    if (offset + 2 < z->size) {
        val |= z->data[offset + 2] << 8;
        ret++;
    }
    if (offset + 3 < z->size) {
        val |= z->data[offset + 3];
        ret++;
    }
    *word = val;
    return ret;
}