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
 int ENOMEM ; 
 uintptr_t LJ_ALLOC_MBITS ; 
 int LJ_ALLOC_MMAP_PROBE_LINEAR ; 
 uintptr_t LJ_ALLOC_MMAP_PROBE_LOWER ; 
 int LJ_ALLOC_MMAP_PROBE_MAX ; 
 int LJ_PAGESIZE ; 
 scalar_t__ LJ_UNLIKELY (int) ; 
 void* MFAIL ; 
 int /*<<< orphan*/  MMAP_FLAGS_PROBE ; 
 int /*<<< orphan*/  MMAP_PROT ; 
 int errno ; 
 void* mmap (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 uintptr_t mmap_probe_seed () ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 

__attribute__((used)) static void *mmap_probe(size_t size)
{
  /* Hint for next allocation. Doesn't need to be thread-safe. */
  static uintptr_t hint_addr = 0;
  static uintptr_t hint_prng = 0;
  int olderr = errno;
  int retry;
  for (retry = 0; retry < LJ_ALLOC_MMAP_PROBE_MAX; retry++) {
    void *p = mmap((void *)hint_addr, size, MMAP_PROT, MMAP_FLAGS_PROBE, -1, 0);
    uintptr_t addr = (uintptr_t)p;
    if ((addr >> LJ_ALLOC_MBITS) == 0 && addr >= LJ_ALLOC_MMAP_PROBE_LOWER) {
      /* We got a suitable address. Bump the hint address. */
      hint_addr = addr + size;
      errno = olderr;
      return p;
    }
    if (p != MFAIL) {
      munmap(p, size);
    } else if (errno == ENOMEM) {
      return MFAIL;
    }
    if (hint_addr) {
      /* First, try linear probing. */
      if (retry < LJ_ALLOC_MMAP_PROBE_LINEAR) {
	hint_addr += 0x1000000;
	if (((hint_addr + size) >> LJ_ALLOC_MBITS) != 0)
	  hint_addr = 0;
	continue;
      } else if (retry == LJ_ALLOC_MMAP_PROBE_LINEAR) {
	/* Next, try a no-hint probe to get back an ASLR address. */
	hint_addr = 0;
	continue;
      }
    }
    /* Finally, try pseudo-random probing. */
    if (LJ_UNLIKELY(hint_prng == 0)) {
      hint_prng = mmap_probe_seed();
    }
    /* The unsuitable address we got has some ASLR PRNG bits. */
    hint_addr ^= addr & ~((uintptr_t)(LJ_PAGESIZE-1));
    do {  /* The PRNG itself is very weak, but see above. */
      hint_prng = hint_prng * 1103515245 + 12345;
      hint_addr ^= hint_prng * (uintptr_t)LJ_PAGESIZE;
      hint_addr &= (((uintptr_t)1 << LJ_ALLOC_MBITS)-1);
    } while (hint_addr < LJ_ALLOC_MMAP_PROBE_LOWER);
  }
  errno = olderr;
  return MFAIL;
}