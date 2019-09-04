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
struct TYPE_3__ {int /*<<< orphan*/  zc; scalar_t__ dictSize; scalar_t__ outEnd; scalar_t__ outStart; scalar_t__ inPos; scalar_t__ hPos; int /*<<< orphan*/  stage; } ;
typedef  TYPE_1__ ZBUFF_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZBUFFds_readHeader ; 
 size_t ZSTD_resetDCtx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ZBUFF_decompressInit(ZBUFF_DCtx* zbc)
{
    zbc->stage = ZBUFFds_readHeader;
    zbc->hPos = zbc->inPos = zbc->outStart = zbc->outEnd = zbc->dictSize = 0;
    return ZSTD_resetDCtx(zbc->zc);
}