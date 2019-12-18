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
typedef  size_t uint64_t ;

/* Variables and functions */
 size_t WEBP_MAX_ALLOCABLE_MEMORY ; 
 scalar_t__ countdown_to_fail ; 
 size_t const mem_limit ; 
 scalar_t__ total_mem ; 

__attribute__((used)) static int CheckSizeArgumentsOverflow(uint64_t nmemb, size_t size) {
  const uint64_t total_size = nmemb * size;
  if (nmemb == 0) return 1;
  if ((uint64_t)size > WEBP_MAX_ALLOCABLE_MEMORY / nmemb) return 0;
  if (total_size != (size_t)total_size) return 0;
#if defined(PRINT_MEM_INFO) && defined(MALLOC_FAIL_AT)
  if (countdown_to_fail > 0 && --countdown_to_fail == 0) {
    return 0;    // fake fail!
  }
#endif
#if defined(MALLOC_LIMIT)
  if (mem_limit > 0) {
    const uint64_t new_total_mem = (uint64_t)total_mem + total_size;
    if (new_total_mem != (size_t)new_total_mem ||
        new_total_mem > mem_limit) {
      return 0;   // fake fail!
    }
  }
#endif

  return 1;
}