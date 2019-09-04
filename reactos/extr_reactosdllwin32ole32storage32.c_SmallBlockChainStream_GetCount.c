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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  SmallBlockChainStream ;

/* Variables and functions */
 scalar_t__ BLOCK_END_OF_CHAIN ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SmallBlockChainStream_GetHeadOfChain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SmallBlockChainStream_GetNextBlockInChain (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static ULONG SmallBlockChainStream_GetCount(SmallBlockChainStream* This)
{
    ULONG blockIndex;
    ULONG count = 0;

    blockIndex = SmallBlockChainStream_GetHeadOfChain(This);

    while(blockIndex != BLOCK_END_OF_CHAIN)
    {
        count++;

        if(FAILED(SmallBlockChainStream_GetNextBlockInChain(This,
                        blockIndex, &blockIndex)))
            return 0;
    }

    return count;
}