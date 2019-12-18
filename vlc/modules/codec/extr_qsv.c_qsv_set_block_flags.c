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
typedef  int uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_TYPE_B ; 
 int /*<<< orphan*/  BLOCK_FLAG_TYPE_I ; 
 int /*<<< orphan*/  BLOCK_FLAG_TYPE_P ; 
 int /*<<< orphan*/  BLOCK_FLAG_TYPE_PB ; 
 int MFX_FRAMETYPE_B ; 
 int MFX_FRAMETYPE_I ; 
 int MFX_FRAMETYPE_IDR ; 
 int MFX_FRAMETYPE_P ; 

__attribute__((used)) static void qsv_set_block_flags(block_t *block, uint16_t frame_type)
{
    if (frame_type & MFX_FRAMETYPE_IDR)
        block->i_flags = BLOCK_FLAG_TYPE_I;
    else if ((frame_type & MFX_FRAMETYPE_P) || (frame_type & MFX_FRAMETYPE_I))
        block->i_flags = BLOCK_FLAG_TYPE_P;
    else if (frame_type & MFX_FRAMETYPE_B)
        block->i_flags = BLOCK_FLAG_TYPE_B;
    else
        block->i_flags = BLOCK_FLAG_TYPE_PB;
}