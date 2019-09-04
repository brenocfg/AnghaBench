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
typedef  scalar_t__ ZSTD_format_e ;

/* Variables and functions */
 scalar_t__ ZSTD_FRAMEHEADERSIZE_PREFIX ; 
 scalar_t__ ZSTD_FRAMEIDSIZE ; 
 int /*<<< orphan*/  ZSTD_STATIC_ASSERT (int) ; 
 scalar_t__ ZSTD_f_zstd1 ; 
 scalar_t__ ZSTD_f_zstd1_magicless ; 
 scalar_t__ ZSTD_frameHeaderSize_prefix ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static size_t ZSTD_startingInputLength(ZSTD_format_e format)
{
    size_t const startingInputLength = (format==ZSTD_f_zstd1_magicless) ?
                    ZSTD_frameHeaderSize_prefix - ZSTD_FRAMEIDSIZE :
                    ZSTD_frameHeaderSize_prefix;
    ZSTD_STATIC_ASSERT(ZSTD_FRAMEHEADERSIZE_PREFIX >= ZSTD_FRAMEIDSIZE);
    /* only supports formats ZSTD_f_zstd1 and ZSTD_f_zstd1_magicless */
    assert( (format == ZSTD_f_zstd1) || (format == ZSTD_f_zstd1_magicless) );
    return startingInputLength;
}