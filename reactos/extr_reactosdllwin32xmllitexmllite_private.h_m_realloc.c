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
typedef  int /*<<< orphan*/  IMalloc ;

/* Variables and functions */
 void* IMalloc_Realloc (int /*<<< orphan*/ *,void*,size_t) ; 
 void* heap_realloc (void*,size_t) ; 

__attribute__((used)) static inline void *m_realloc(IMalloc *imalloc, void *mem, size_t len)
{
    if (imalloc)
        return IMalloc_Realloc(imalloc, mem, len);
    else
        return heap_realloc(mem, len);
}