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
struct TYPE_2__ {int block_len; } ;
struct chmFile {scalar_t__ reset_blkcount; scalar_t__ lzx_last_block; int cache_num_blocks; int* cache_block_indices; TYPE_1__ reset_table; int /*<<< orphan*/  lzx_state; int /*<<< orphan*/ ** cache_blocks; } ;
typedef  scalar_t__ UInt64 ;
typedef  int UInt32 ;
typedef  int /*<<< orphan*/  UChar ;
typedef  int Int64 ;

/* Variables and functions */
 scalar_t__ DECR_OK ; 
 scalar_t__ LZXdecompress (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  LZXreset (int /*<<< orphan*/ ) ; 
 int _chm_fetch_bytes (struct chmFile*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  _chm_get_cmpblock_bounds (struct chmFile*,scalar_t__,scalar_t__*,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (unsigned int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static Int64 _chm_decompress_block(struct chmFile *h,
                                   UInt64 block,
                                   UChar **ubuffer)
{
    UChar *cbuffer = malloc(((unsigned int)h->reset_table.block_len + 6144));
    UInt64 cmpStart;                                    /* compressed start  */
    Int64 cmpLen;                                       /* compressed len    */
    int indexSlot;                                      /* cache index slot  */
    UChar *lbuffer;                                     /* local buffer ptr  */
    UInt32 blockAlign = (UInt32)(block % h->reset_blkcount); /* reset intvl. aln. */
    UInt32 i;                                           /* local loop index  */

    if (cbuffer == NULL)
        return -1;

    /* let the caching system pull its weight! */
    if (block - blockAlign <= h->lzx_last_block  &&
        block              >= h->lzx_last_block)
        blockAlign = (block - h->lzx_last_block);

    /* check if we need previous blocks */
    if (blockAlign != 0)
    {
        /* fetch all required previous blocks since last reset */
        for (i = blockAlign; i > 0; i--)
        {
            UInt32 curBlockIdx = block - i;

            /* check if we most recently decompressed the previous block */
            if (h->lzx_last_block != (int)curBlockIdx)
            {
                if ((curBlockIdx % h->reset_blkcount) == 0)
                {
#ifdef CHM_DEBUG
                    fprintf(stderr, "***RESET (1)***\n");
#endif
                    LZXreset(h->lzx_state);
                }

                indexSlot = (int)((curBlockIdx) % h->cache_num_blocks);
                if (! h->cache_blocks[indexSlot])
                    h->cache_blocks[indexSlot] = (UChar *)malloc((unsigned int)(h->reset_table.block_len));
                if (! h->cache_blocks[indexSlot])
                {
                    free(cbuffer);
                    return -1;
                }
                h->cache_block_indices[indexSlot] = curBlockIdx;
                lbuffer = h->cache_blocks[indexSlot];

                /* decompress the previous block */
#ifdef CHM_DEBUG
                fprintf(stderr, "Decompressing block #%4d (EXTRA)\n", curBlockIdx);
#endif
                if (!_chm_get_cmpblock_bounds(h, curBlockIdx, &cmpStart, &cmpLen) ||
                    cmpLen < 0                                                    ||
                    cmpLen > h->reset_table.block_len + 6144                      ||
                    _chm_fetch_bytes(h, cbuffer, cmpStart, cmpLen) != cmpLen      ||
                    LZXdecompress(h->lzx_state, cbuffer, lbuffer, (int)cmpLen,
                                  (int)h->reset_table.block_len) != DECR_OK)
                {
#ifdef CHM_DEBUG
                    fprintf(stderr, "   (DECOMPRESS FAILED!)\n");
#endif
                    free(cbuffer);
                    return (Int64)0;
                }

                h->lzx_last_block = (int)curBlockIdx;
            }
        }
    }
    else
    {
        if ((block % h->reset_blkcount) == 0)
        {
#ifdef CHM_DEBUG
            fprintf(stderr, "***RESET (2)***\n");
#endif
            LZXreset(h->lzx_state);
        }
    }

    /* allocate slot in cache */
    indexSlot = (int)(block % h->cache_num_blocks);
    if (! h->cache_blocks[indexSlot])
        h->cache_blocks[indexSlot] = (UChar *)malloc(((unsigned int)h->reset_table.block_len));
    if (! h->cache_blocks[indexSlot])
    {
        free(cbuffer);
        return -1;
    }
    h->cache_block_indices[indexSlot] = block;
    lbuffer = h->cache_blocks[indexSlot];
    *ubuffer = lbuffer;

    /* decompress the block we actually want */
#ifdef CHM_DEBUG
    fprintf(stderr, "Decompressing block #%4d (REAL )\n", block);
#endif
    if (! _chm_get_cmpblock_bounds(h, block, &cmpStart, &cmpLen)          ||
        _chm_fetch_bytes(h, cbuffer, cmpStart, cmpLen) != cmpLen          ||
        LZXdecompress(h->lzx_state, cbuffer, lbuffer, (int)cmpLen,
                      (int)h->reset_table.block_len) != DECR_OK)
    {
#ifdef CHM_DEBUG
        fprintf(stderr, "   (DECOMPRESS FAILED!)\n");
#endif
        free(cbuffer);
        return (Int64)0;
    }
    h->lzx_last_block = (int)block;

    /* XXX: modify LZX routines to return the length of the data they
     * decompressed and return that instead, for an extra sanity check.
     */
    free(cbuffer);
    return h->reset_table.block_len;
}