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
typedef  scalar_t__ ZSTD_strategy ;
struct TYPE_3__ {int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ const ZSTD_blockCompressor ;
typedef  size_t U32 ;

/* Variables and functions */
#define  ZSTD_compressBlock_btlazy2 143 
#define  ZSTD_compressBlock_btlazy2_extDict 142 
#define  ZSTD_compressBlock_btopt 141 
#define  ZSTD_compressBlock_btopt2 140 
#define  ZSTD_compressBlock_btopt2_extDict 139 
#define  ZSTD_compressBlock_btopt_extDict 138 
#define  ZSTD_compressBlock_doubleFast 137 
#define  ZSTD_compressBlock_doubleFast_extDict 136 
#define  ZSTD_compressBlock_fast 135 
#define  ZSTD_compressBlock_fast_extDict 134 
#define  ZSTD_compressBlock_greedy 133 
#define  ZSTD_compressBlock_greedy_extDict 132 
#define  ZSTD_compressBlock_lazy 131 
#define  ZSTD_compressBlock_lazy2 130 
#define  ZSTD_compressBlock_lazy2_extDict 129 
#define  ZSTD_compressBlock_lazy_extDict 128 

__attribute__((used)) static ZSTD_blockCompressor ZSTD_selectBlockCompressor(ZSTD_strategy strat, int extDict)
{
	static const ZSTD_blockCompressor blockCompressor[2][8] = {
	    {ZSTD_compressBlock_fast, ZSTD_compressBlock_doubleFast, ZSTD_compressBlock_greedy, ZSTD_compressBlock_lazy, ZSTD_compressBlock_lazy2,
	     ZSTD_compressBlock_btlazy2, ZSTD_compressBlock_btopt, ZSTD_compressBlock_btopt2},
	    {ZSTD_compressBlock_fast_extDict, ZSTD_compressBlock_doubleFast_extDict, ZSTD_compressBlock_greedy_extDict, ZSTD_compressBlock_lazy_extDict,
	     ZSTD_compressBlock_lazy2_extDict, ZSTD_compressBlock_btlazy2_extDict, ZSTD_compressBlock_btopt_extDict, ZSTD_compressBlock_btopt2_extDict}};

	return blockCompressor[extDict][(U32)strat];
}