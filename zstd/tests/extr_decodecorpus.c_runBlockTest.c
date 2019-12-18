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
 int /*<<< orphan*/  DISPLAY (char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_getErrorName (size_t const) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 scalar_t__ generateCompressedBlock (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gt_block ; 
 int /*<<< orphan*/  initDictInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t testDecodeRawBlock (int /*<<< orphan*/ *) ; 
 size_t testDecodeWithDict (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int runBlockTest(U32* seed)
{
    frame_t fr;
    U32 const seedCopy = *seed;
    {   dictInfo const info = initDictInfo(0, 0, NULL, 0);
        *seed = generateCompressedBlock(*seed, &fr, info);
    }

    {   size_t const r = testDecodeRawBlock(&fr);
        if (ZSTD_isError(r)) {
            DISPLAY("Error in block mode on test seed %u: %s\n",
                    (unsigned)seedCopy, ZSTD_getErrorName(r));
            return 1;
        }
    }

    {   size_t const r = testDecodeWithDict(*seed, gt_block);
        if (ZSTD_isError(r)) {
            DISPLAY("Error in block mode with dictionary on test seed %u: %s\n",
                    (unsigned)seedCopy, ZSTD_getErrorName(r));
            return 1;
        }
    }
    return 0;
}