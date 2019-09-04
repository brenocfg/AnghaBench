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
typedef  int WORD ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 

__attribute__((used)) static NTSTATUS
RtlpCompressBufferLZNT1(UCHAR *src, ULONG src_size, UCHAR *dst, ULONG dst_size,
                        ULONG chunk_size, ULONG *final_size, UCHAR *workspace)
{
        UCHAR *src_cur = src, *src_end = src + src_size;
        UCHAR *dst_cur = dst, *dst_end = dst + dst_size;
        ULONG block_size;

        while (src_cur < src_end)
        {
            /* determine size of current chunk */
            block_size = min(0x1000, src_end - src_cur);
            if (dst_cur + sizeof(WORD) + block_size > dst_end)
                return STATUS_BUFFER_TOO_SMALL;

            /* write (uncompressed) chunk header */
            *(WORD *)dst_cur = 0x3000 | (block_size - 1);
            dst_cur += sizeof(WORD);

            /* write chunk content */
            memcpy(dst_cur, src_cur, block_size);
            dst_cur += block_size;
            src_cur += block_size;
        }

        if (final_size)
            *final_size = dst_cur - dst;

        return STATUS_SUCCESS;
}