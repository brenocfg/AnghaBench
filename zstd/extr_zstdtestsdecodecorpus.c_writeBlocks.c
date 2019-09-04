#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t contentSize; size_t windowSize; } ;
struct TYPE_6__ {TYPE_1__ header; } ;
typedef  TYPE_2__ frame_t ;
typedef  int /*<<< orphan*/  dictInfo ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int MIN (size_t const,size_t) ; 
 int RAND (int /*<<< orphan*/ *) ; 
 size_t const g_maxBlockSize ; 
 int /*<<< orphan*/  writeBlock (int /*<<< orphan*/ *,TYPE_2__*,size_t,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void writeBlocks(U32* seed, frame_t* frame, dictInfo info)
{
    size_t contentLeft = frame->header.contentSize;
    size_t const maxBlockSize = MIN(g_maxBlockSize, frame->header.windowSize);
    while (1) {
        /* 1 in 4 chance of ending frame */
        int const lastBlock = contentLeft > maxBlockSize ? 0 : !(RAND(seed) & 3);
        size_t blockContentSize;
        if (lastBlock) {
            blockContentSize = contentLeft;
        } else {
            if (contentLeft > 0 && (RAND(seed) & 7)) {
                /* some variable size block */
                blockContentSize = RAND(seed) % (MIN(maxBlockSize, contentLeft)+1);
            } else if (contentLeft > maxBlockSize && (RAND(seed) & 1)) {
                /* some full size block */
                blockContentSize = maxBlockSize;
            } else {
                /* some empty block */
                blockContentSize = 0;
            }
        }

        writeBlock(seed, frame, blockContentSize, lastBlock, info);

        contentLeft -= blockContentSize;
        if (lastBlock) break;
    }
}