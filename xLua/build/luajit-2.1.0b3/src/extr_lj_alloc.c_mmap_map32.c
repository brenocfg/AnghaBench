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
 scalar_t__ LJ_ALLOC_MMAP32_START ; 
 int MAP_32BIT ; 
 void* MFAIL ; 
 int MMAP_FLAGS ; 
 int /*<<< orphan*/  MMAP_PROT ; 
 int errno ; 
 void* mmap (void*,size_t,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 void* mmap_probe (size_t) ; 

__attribute__((used)) static void *mmap_map32(size_t size)
{
#if LJ_ALLOC_MMAP_PROBE
  static int fallback = 0;
  if (fallback)
    return mmap_probe(size);
#endif
  {
    int olderr = errno;
    void *ptr = mmap((void *)LJ_ALLOC_MMAP32_START, size, MMAP_PROT, MAP_32BIT|MMAP_FLAGS, -1, 0);
    errno = olderr;
    /* This only allows 1GB on Linux. So fallback to probing to get 2GB. */
#if LJ_ALLOC_MMAP_PROBE
    if (ptr == MFAIL) {
      fallback = 1;
      return mmap_probe(size);
    }
#endif
    return ptr;
  }
}