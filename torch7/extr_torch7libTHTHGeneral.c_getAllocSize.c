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
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static ptrdiff_t getAllocSize(void *ptr) {
#if defined(__unix) && defined(HAVE_MALLOC_USABLE_SIZE)
  return malloc_usable_size(ptr);
#elif defined(__APPLE__)
  return malloc_size(ptr);
#elif defined(_WIN32)
  if(ptr) { return _msize(ptr); } else { return 0; }
#else
  return 0;
#endif
}