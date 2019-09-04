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
typedef  int /*<<< orphan*/  urlcache_header ;
typedef  int /*<<< orphan*/  entry_hash_table ;
typedef  scalar_t__ LPBYTE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */

__attribute__((used)) static inline entry_hash_table* urlcache_get_hash_table(const urlcache_header *pHeader, DWORD dwOffset)
{
    if(!dwOffset)
        return NULL;
    return (entry_hash_table*)((LPBYTE)pHeader + dwOffset);
}