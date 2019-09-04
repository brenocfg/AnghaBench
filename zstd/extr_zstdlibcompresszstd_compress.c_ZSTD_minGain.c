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
typedef  scalar_t__ strat ;
typedef  int ZSTD_strategy ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_STATIC_ASSERT (int) ; 
 int ZSTD_btultra ; 
 int /*<<< orphan*/  ZSTD_cParam_withinBounds (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZSTD_c_strategy ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ZSTD_minGain(size_t srcSize, ZSTD_strategy strat)
{
    U32 const minlog = (strat>=ZSTD_btultra) ? (U32)(strat) - 1 : 6;
    ZSTD_STATIC_ASSERT(ZSTD_btultra == 8);
    assert(ZSTD_cParam_withinBounds(ZSTD_c_strategy, strat));
    return (srcSize >> minlog) + 2;
}