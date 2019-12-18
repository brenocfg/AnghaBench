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
typedef  int /*<<< orphan*/  frame_t ;
typedef  int /*<<< orphan*/  dictInfo ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,unsigned int) ; 
 int /*<<< orphan*/  initFrame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeBlocks (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeChecksum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeFrameHeader (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static U32 generateFrame(U32 seed, frame_t* fr, dictInfo info)
{
    /* generate a complete frame */
    DISPLAYLEVEL(3, "frame seed: %u\n", (unsigned)seed);
    initFrame(fr);

    writeFrameHeader(&seed, fr, info);
    writeBlocks(&seed, fr, info);
    writeChecksum(fr);

    return seed;
}