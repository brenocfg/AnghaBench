#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int const windowLog; } ;
struct TYPE_5__ {TYPE_1__ cParams; } ;
typedef  TYPE_2__ ZSTD_parameters ;

/* Variables and functions */
 TYPE_2__ ZSTD_getParams (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_maxCLevel () ; 

__attribute__((used)) static size_t getUseableDictSize(unsigned compressionLevel)
{
    ZSTD_parameters const params = ZSTD_getParams(compressionLevel, 0, 0);
    unsigned const overlapLog = compressionLevel >= (unsigned)ZSTD_maxCLevel() ? 0 : 3;
    size_t const overlapSize = 1 << (params.cParams.windowLog - overlapLog);
    return overlapSize;
}