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
 void* ExAllocatePoolWithTag (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  ZSTD_ALLOC_TAG ; 

__attribute__((used)) static void* zstd_malloc(void* opaque, size_t size) {
    UNUSED(opaque);

    return ExAllocatePoolWithTag(PagedPool, size, ZSTD_ALLOC_TAG);
}