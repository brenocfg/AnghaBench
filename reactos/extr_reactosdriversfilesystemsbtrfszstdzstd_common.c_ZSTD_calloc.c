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
struct TYPE_3__ {void* (* customAlloc ) (int /*<<< orphan*/ ,size_t) ;int /*<<< orphan*/  opaque; } ;
typedef  TYPE_1__ ZSTD_customMem ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void* const,int /*<<< orphan*/ ,size_t) ; 
 void* stub1 (int /*<<< orphan*/ ,size_t) ; 

void* ZSTD_calloc(size_t size, ZSTD_customMem customMem)
{
    /* calloc implemented as malloc+memset;
        * not as efficient as calloc, but next best guess for custom malloc */
    void* const ptr = customMem.customAlloc(customMem.opaque, size);
    memset(ptr, 0, size);
    return ptr;
}