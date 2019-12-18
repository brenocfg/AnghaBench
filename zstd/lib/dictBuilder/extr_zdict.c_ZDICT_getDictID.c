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

/* Variables and functions */
 int MEM_readLE32 (char const*) ; 
 scalar_t__ ZSTD_MAGIC_DICTIONARY ; 

unsigned ZDICT_getDictID(const void* dictBuffer, size_t dictSize)
{
    if (dictSize < 8) return 0;
    if (MEM_readLE32(dictBuffer) != ZSTD_MAGIC_DICTIONARY) return 0;
    return MEM_readLE32((const char*)dictBuffer + 4);
}