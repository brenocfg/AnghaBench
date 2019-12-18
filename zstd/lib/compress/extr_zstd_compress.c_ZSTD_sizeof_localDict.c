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
struct TYPE_3__ {size_t dictSize; int /*<<< orphan*/  cdict; int /*<<< orphan*/ * dictBuffer; } ;
typedef  TYPE_1__ ZSTD_localDict ;

/* Variables and functions */
 size_t ZSTD_sizeof_CDict (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ZSTD_sizeof_localDict(ZSTD_localDict dict)
{
    size_t const bufferSize = dict.dictBuffer != NULL ? dict.dictSize : 0;
    size_t const cdictSize = ZSTD_sizeof_CDict(dict.cdict);
    return bufferSize + cdictSize;
}