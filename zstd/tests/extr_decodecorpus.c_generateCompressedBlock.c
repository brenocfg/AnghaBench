#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int windowSize; } ;
struct TYPE_7__ {int /*<<< orphan*/ * src; int /*<<< orphan*/  oldStats; int /*<<< orphan*/  stats; int /*<<< orphan*/ * data; TYPE_1__ header; } ;
typedef  TYPE_2__ frame_t ;
typedef  int /*<<< orphan*/  dictInfo ;
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 int MAX_WINDOW_LOG ; 
 size_t MIN (unsigned int,int) ; 
 size_t const RAND (scalar_t__*) ; 
 unsigned int g_maxBlockSize ; 
 int /*<<< orphan*/  initFrame (TYPE_2__*) ; 
 size_t writeCompressedBlock (scalar_t__*,TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static U32 generateCompressedBlock(U32 seed, frame_t* frame, dictInfo info)
{
    size_t blockContentSize;
    int blockWritten = 0;
    BYTE* op;
    DISPLAYLEVEL(4, "block seed: %u\n", (unsigned)seed);
    initFrame(frame);
    op = (BYTE*)frame->data;

    while (!blockWritten) {
        size_t cSize;
        /* generate window size */
        {   int const exponent = RAND(&seed) % (MAX_WINDOW_LOG - 10);
            int const mantissa = RAND(&seed) % 8;
            frame->header.windowSize = (1U << (exponent + 10));
            frame->header.windowSize += (frame->header.windowSize / 8) * mantissa;
        }

        /* generate content size */
        {   size_t const maxBlockSize = MIN(g_maxBlockSize, frame->header.windowSize);
            if (RAND(&seed) & 15) {
                /* some full size blocks */
                blockContentSize = maxBlockSize;
            } else if (RAND(&seed) & 7 && g_maxBlockSize >= (1U << 7)) {
                /* some small blocks <= 128 bytes*/
                blockContentSize = RAND(&seed) % (1U << 7);
            } else {
                /* some variable size blocks */
                blockContentSize = RAND(&seed) % maxBlockSize;
            }
        }

        /* try generating a compressed block */
        frame->oldStats = frame->stats;
        frame->data = op;
        cSize = writeCompressedBlock(&seed, frame, blockContentSize, info);
        if (cSize >= blockContentSize) {  /* compressed size must be strictly smaller than decompressed size : https://github.com/facebook/zstd/blob/dev/doc/zstd_compression_format.md#blocks */
            /* data doesn't compress -- try again */
            frame->stats = frame->oldStats; /* don't update the stats */
            DISPLAYLEVEL(5, "   can't compress block : try again \n");
        } else {
            blockWritten = 1;
            DISPLAYLEVEL(4, "   block size: %u \n", (unsigned)cSize);
            frame->src = (BYTE*)frame->src + blockContentSize;
        }
    }
    return seed;
}