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
typedef  int /*<<< orphan*/  mm_backup_ctx ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMBAK_TAG_BIND_VARINT ; 
 int /*<<< orphan*/  MMBAK_TAG_BIND_VARINT_MINUS ; 
 int dump_write_stream (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int dump_write_varint(mm_backup_ctx *ctx, int64_t val)
{
    uint8_t buf[12];
    uint8_t *p = buf;

    if (val < 0) {
        *p++ = MMBAK_TAG_BIND_VARINT_MINUS;
        val = ~val;
    } else
        *p++ = MMBAK_TAG_BIND_VARINT;

    do {
        uint8_t b = val & 0x7F;
        val >>= 7;
        if (val)
            b |= 0x80;
        *p++ = b;
    } while (val);

    return dump_write_stream(ctx, buf, p - buf);
}