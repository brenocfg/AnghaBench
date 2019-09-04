#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {void* noDictIDFlag; void* checksumFlag; void* contentSizeFlag; } ;
typedef  TYPE_1__ ZSTD_frameParameters ;

/* Variables and functions */
 void* FUZZ_rand32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

ZSTD_frameParameters FUZZ_randomFParams(uint32_t *state)
{
    /* Select frame parameters */
    ZSTD_frameParameters fParams;
    fParams.contentSizeFlag = FUZZ_rand32(state, 0, 1);
    fParams.checksumFlag = FUZZ_rand32(state, 0, 1);
    fParams.noDictIDFlag = FUZZ_rand32(state, 0, 1);
    return fParams;
}