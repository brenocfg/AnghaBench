#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* litlength_repeatMode; void* matchlength_repeatMode; void* offcode_repeatMode; } ;
struct TYPE_6__ {int /*<<< orphan*/  repeatMode; } ;
struct TYPE_7__ {TYPE_3__ fse; TYPE_1__ huf; } ;
struct TYPE_9__ {TYPE_2__ entropy; int /*<<< orphan*/ * rep; } ;
typedef  TYPE_4__ ZSTD_compressedBlockState_t ;

/* Variables and functions */
 void* FSE_repeat_none ; 
 int /*<<< orphan*/  HUF_repeat_none ; 
 int ZSTD_REP_NUM ; 
 int /*<<< orphan*/ * repStartValue ; 

__attribute__((used)) static void ZSTD_reset_compressedBlockState(ZSTD_compressedBlockState_t* bs)
{
    int i;
    for (i = 0; i < ZSTD_REP_NUM; ++i)
        bs->rep[i] = repStartValue[i];
    bs->entropy.huf.repeatMode = HUF_repeat_none;
    bs->entropy.fse.offcode_repeatMode = FSE_repeat_none;
    bs->entropy.fse.matchlength_repeatMode = FSE_repeat_none;
    bs->entropy.fse.litlength_repeatMode = FSE_repeat_none;
}