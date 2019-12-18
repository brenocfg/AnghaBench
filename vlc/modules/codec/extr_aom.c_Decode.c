#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_5__ {int i_flags; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int /*<<< orphan*/  OutputFrame ; 
 int /*<<< orphan*/  PopFrames (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PushFrame (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int VLCDEC_SUCCESS ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 

__attribute__((used)) static int Decode(decoder_t *dec, block_t *block)
{
    if (block && block->i_flags & (BLOCK_FLAG_CORRUPTED))
    {
        block_Release(block);
        return VLCDEC_SUCCESS;
    }

    int i_ret = PushFrame(dec, block);

    PopFrames(dec, OutputFrame);

    return i_ret;
}