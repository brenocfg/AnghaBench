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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  mm_backup_ctx ;

/* Variables and functions */
 scalar_t__ MMBAK_TAG_BIND_BLOB ; 
 scalar_t__ MMBAK_TAG_BIND_TEXT ; 
 int /*<<< orphan*/  MMBAK_TAG_LARGE_DATA ; 
 int dump_write_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dump_write_byte_byte (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int dump_write_byte_short (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int dump_write_short (int /*<<< orphan*/ *,int) ; 
 int dump_write_stream (int /*<<< orphan*/ *,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
dump_write_blob(mm_backup_ctx *ctx, uint8_t tag, const void *data, int size)
{
    const char *p = (const char *) data;
    int ret;

    if (size < 0)
        size = strlen(p);

    if (size >= 65536) {
        uint32_t ext_size = size & 0xFFFF0000;
        uint16_t blocks = ext_size >> 16;
        ret = dump_write_byte(ctx, MMBAK_TAG_LARGE_DATA);
        ret |= dump_write_short(ctx, blocks);
        ret |= dump_write_stream(ctx, p, ext_size);
        if (ret != 0)
            return -1;
        size -= ext_size;
        p += ext_size;
    }

    if (size < 256 &&
        (tag == MMBAK_TAG_BIND_TEXT || tag == MMBAK_TAG_BIND_BLOB))
        ret = dump_write_byte_byte(ctx, ++tag, (uint8_t) size);
    else
        ret = dump_write_byte_short(ctx, tag, (uint16_t) size);
    ret |= dump_write_stream(ctx, p, size);
    if (ret != 0)
        return -1;

    return 0;
}