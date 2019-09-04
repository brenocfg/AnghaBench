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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  mm_recover_ctx ;
typedef  int int64_t ;

/* Variables and functions */
 int MMBAK_RET_FAILED ; 
 int dump_read_stream (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int dump_read_varint(mm_recover_ctx *ctx, int64_t *val, int minus)
{
    uint8_t b;
    int ret;
    int64_t v = 0;
    int shift = 0;

    do {
        ret = dump_read_stream(ctx, &b, 1);
        if (ret != 1)
            return MMBAK_RET_FAILED;

        v |= (int64_t)(b & 0x7F) << shift;
        shift += 7;
    } while (b & 0x80);

    if (minus)
        v = ~v;
    *val = v;
    return 0;
}