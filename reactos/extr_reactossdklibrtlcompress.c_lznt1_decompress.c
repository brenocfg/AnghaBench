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
 int /*<<< orphan*/  STATUS_ACCESS_VIOLATION ; 
 int /*<<< orphan*/  STATUS_BAD_COMPRESSION_BUFFER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/ * lznt1_decompress_chunk (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 

__attribute__((used)) static NTSTATUS lznt1_decompress(UCHAR *dst, ULONG dst_size, UCHAR *src, ULONG src_size,
                                 ULONG offset, ULONG *final_size, UCHAR *workspace)
{
    UCHAR *src_cur = src, *src_end = src + src_size;
    UCHAR *dst_cur = dst, *dst_end = dst + dst_size;
    ULONG chunk_size, block_size;
    WORD chunk_header;
    UCHAR *ptr;

    if (src_cur + sizeof(WORD) > src_end)
        return STATUS_BAD_COMPRESSION_BUFFER;

    /* skip over chunks which have a big distance (>= 0x1000) to the destination offset */
    while (offset >= 0x1000 && src_cur + sizeof(WORD) <= src_end)
    {
        /* read chunk header and extract size */
        chunk_header = *(WORD *)src_cur;
        src_cur += sizeof(WORD);
        if (!chunk_header) goto out;
        chunk_size = (chunk_header & 0xFFF) + 1;

        /* ensure we have enough buffer to process chunk */
        if (src_cur + chunk_size > src_end)
            return STATUS_BAD_COMPRESSION_BUFFER;

        src_cur += chunk_size;
        offset  -= 0x1000;
    }

    /* this chunk is can be included partially */
    if (offset && src_cur + sizeof(WORD) <= src_end)
    {
        /* read chunk header and extract size */
        chunk_header = *(WORD *)src_cur;
        src_cur += sizeof(WORD);
        if (!chunk_header) goto out;
        chunk_size = (chunk_header & 0xFFF) + 1;

        /* ensure we have enough buffer to process chunk */
        if (src_cur + chunk_size > src_end)
            return STATUS_BAD_COMPRESSION_BUFFER;

        if (dst_cur >= dst_end)
            goto out;

        if (chunk_header & 0x8000)
        {
            /* compressed chunk */
            if (!workspace) return STATUS_ACCESS_VIOLATION;
            ptr = lznt1_decompress_chunk(workspace, 0x1000, src_cur, chunk_size);
            if (!ptr) return STATUS_BAD_COMPRESSION_BUFFER;
            if (ptr - workspace > offset)
            {
                block_size = min((ptr - workspace) - offset, dst_end - dst_cur);
                memcpy(dst_cur, workspace + offset, block_size);
                dst_cur += block_size;
            }
        }
        else
        {
            /* uncompressed chunk */
            if (chunk_size > offset)
            {
                block_size = min(chunk_size - offset, dst_end - dst_cur);
                memcpy(dst_cur, src_cur + offset, block_size);
                dst_cur += block_size;
            }
        }

        src_cur += chunk_size;
    }

    /* handle remaining chunks */
    while (src_cur + sizeof(WORD) <= src_end)
    {
        /* read chunk header and extract size */
        chunk_header = *(WORD *)src_cur;
        src_cur += sizeof(WORD);
        if (!chunk_header) goto out;
        chunk_size = (chunk_header & 0xFFF) + 1;

        if (src_cur + chunk_size > src_end)
            return STATUS_BAD_COMPRESSION_BUFFER;

        /* add padding if required */
        block_size = ((dst_cur - dst) + offset) & 0xFFF;
        if (block_size)
        {
            block_size = 0x1000 - block_size;
            if (dst_cur + block_size >= dst_end)
                goto out;
            memset(dst_cur, 0, block_size);
            dst_cur += block_size;
        }

        if (dst_cur >= dst_end)
            goto out;

        if (chunk_header & 0x8000)
        {
            /* compressed chunk */
            dst_cur = lznt1_decompress_chunk(dst_cur, dst_end - dst_cur, src_cur, chunk_size);
            if (!dst_cur) return STATUS_BAD_COMPRESSION_BUFFER;
        }
        else
        {
            /* uncompressed chunk */
            block_size = min(chunk_size, dst_end - dst_cur);
            memcpy(dst_cur, src_cur, block_size);
            dst_cur += block_size;
        }

        src_cur += chunk_size;
    }

out:
    if (final_size)
        *final_size = dst_cur - dst;

    return STATUS_SUCCESS;

}