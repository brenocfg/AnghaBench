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
 void* EngAllocMem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_FREETYPE ; 

void *
malloc(size_t Size)
{
    void *Object;

    Object = EngAllocMem(0, sizeof(size_t) + Size, TAG_FREETYPE);
    if (Object != NULL)
    {
        *((size_t *)Object) = Size;
        Object = (void *)((size_t *)Object + 1);
    }

    return Object;
}