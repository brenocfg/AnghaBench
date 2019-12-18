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
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  THHeapUpdate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getAllocSize (void*) ; 
 void* malloc (int) ; 
 scalar_t__ posix_memalign (void**,int,int) ; 

__attribute__((used)) static void* THAllocInternal(ptrdiff_t size)
{
  void *ptr;

  if (size > 5120)
  {
#if (defined(__unix) || defined(__APPLE__)) && (!defined(DISABLE_POSIX_MEMALIGN))
    if (posix_memalign(&ptr, 64, size) != 0)
      ptr = NULL;
/*
#elif defined(_WIN32)
    ptr = _aligned_malloc(size, 64);
*/
#else
    ptr = malloc(size);
#endif
  }
  else
  {
    ptr = malloc(size);
  }

  THHeapUpdate(getAllocSize(ptr));
  return ptr;
}